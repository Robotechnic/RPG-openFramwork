#include "map.h"

Map::Map()
{

}

bool Map::loadMap(string map){
    filesystem::path mapPath(map);

    if(this->mapLoader.load(mapPath)){ //try to load the map
        //load the tile map
        this->mapLoader = this->mapLoader.getChild("map");
        if (!this->mapLoader){ //verify if map exist
            ofLogError()<<"Wrong xml format";
            return false;
        }
        //get width and height of the map
        this->height = this->mapLoader.getAttribute("width").getIntValue();
        this->width = this->mapLoader.getAttribute("height").getIntValue();
        //get the width and height of tiles
        this->tilesWidth = this->mapLoader.getAttribute("tilewidth").getIntValue();
        this->tilesHieght = this->mapLoader.getAttribute("tileheight").getIntValue();
        if (this->height == 0 || this->width == 0 || this->tilesWidth == 0 || this->tilesHieght == 0){
            ofLogError()<<"Wrong xml map atributes";
            return false;
        }


        //veriffy if the source of tileset is valid
        ofXml xmlTileSetReference = this->mapLoader.getChild("tileset");
        string tileSetPathString = xmlTileSetReference.getAttribute("source").getValue();
        if (tileSetPathString == ""){
            ofLogError()<<"Wrong xml tileset atributes";
            return false;
        }

        //verify if tile set description can be oppen
        //only one tile set supported for the moment
        //ofLogWarning()<<tileSetPathString.substr(3,tileSetPathString.size()-1);
        filesystem::path tileSetPath(tileSetPathString.substr(3,tileSetPathString.size()-1));
        if(this->tilesLoader.load(tileSetPath)){
            this->tilesLoader = this->tilesLoader.getChild("tileset");
            //getAttributes of tilset to verify informations
            this->columns = this->tilesLoader.getAttribute("columns").getIntValue();
            if (this->columns == 0){
                ofLogError()<<"Wrong xml attributes";
                return false;
            }

            if (this->tilesWidth != this->tilesLoader.getAttribute("tilewidth").getIntValue() ||
                this->tilesHieght != this->tilesLoader.getAttribute("tileheight").getIntValue()){
                ofLogError()<<"Wrong tiles width and height";
                return false;
            }

            ofXml tileSetImageSource = this->tilesLoader.getChild("image");
            if(!tileSetImageSource){
                ofLogError()<<"Wrong xml tileset format";
                return false;
            }

            //verify if path of tile exist
            string tilesetImagePath = tileSetImageSource.getAttribute("source").getValue();
            if (tilesetImagePath == ""){
                ofLogError()<<"Wrong xml tileset atributes";
                return false;
            }
            tilesetImagePath = tileSetPath.remove_filename().generic_string() + "/" + tilesetImagePath;


            //ofLogWarning()<<tilesetImagePath;

            //load image
            if (this->tileSetImage.load(tilesetImagePath)){
                if (this->tileSetImage.getWidth() == tileSetImageSource.getAttribute("width").getIntValue() ||
                        this->tileSetImage.getHeight() == tileSetImageSource.getAttribute("height").getIntValue()){
                    if(!this->createTileSetMap()){
                        return false;
                    }
                } else {
                    ofLogError()<<"Wrong image size";
                    return false;
                }

            } else {
                 ofLogError()<<"Wrong image path";
                 return false;
            }

            //get all layers of the map
            auto mapData = this->mapLoader.getChildren("layer");
            for (ofXml layer : mapData){
                ofXml data = layer.getChild("data");
                if (data){
                    tiles.push_back(vector<vector<int>>()); //add layer to tiles vector
                    //ofLogWarning()<<data.getAttribute("encoding").getValue();
                    if (data.getAttribute("encoding").getValue() == "csv") //verify if encoding is csv
                    {
                        //split data and store it in vector
                        string mapStringData = data.getValue();
                        mapStringData = mapStringData.substr(1,mapStringData.size()-2);
                        vector<string> mapLines = ofSplitString(mapStringData,"\n");
                        for (string linesTileString : mapLines){
                            vector <int> tilesLines;
                            linesTileString = linesTileString.substr(0,linesTileString.size()-2);
                            vector <string> tilesColumn = ofSplitString(linesTileString,",");
                            for (string columnTile : tilesColumn){
                                tilesLines.push_back(ofToInt(columnTile));
                            }
                            this->tiles.at(this->tiles.size()-1).push_back(tilesLines);
                        }
                    } else {
                        ofLogError()<<"Wrong data encoding";
                        return false;
                    }
                }
            }
            //everithing loaded !
            return true;

        } else {
            ofLogError()<<"Tileset does not exist";
        }
    }
    else{
        ofLogError()<<"Map does not exist";
    }
    return false;
}

bool Map::createTileSetMap(){
    //first get tiles
    auto tiles = this->tilesLoader.getChildren("tile");
    //lad all tiles in map tileSet
    for (ofXml tileDescriptor : tiles){
        if (tileDescriptor.getChild("animation")){ // if tile have annimation
            int id = tileDescriptor.getAttribute("id").getIntValue();

            vector<glm::vec2> framesVec;

            for (ofXml frame : tileDescriptor.getChild("animation").getChildren("frame")){
                int tileId = frame.getAttribute("tileid").getIntValue();
                int durration = frame.getAttribute("duration").getIntValue();
                if (tileId == 0 || durration == 0){
                    ofLogError()<<"Wrong frame xml attributes";
                    return false;
                }
                framesVec.push_back(glm::vec2(tileId,durration));
            }

            this->annimTileSet.insert(make_pair(id,Tile(id,framesVec)));
        }

    }
    return true;
}


void Map::draw(int x, int y, int width, int height){
    int xMin = x/this->tilesWidth-1;
    xMin = xMin<0 ? 0 : xMin;
    int yMin = y/this->tilesHieght-1;
    yMin = yMin<0 ? 0 : yMin;
    int xMax = (width)/this->tilesWidth+1;
    xMax = xMax>this->width ? this->width : xMax;
    int yMax = (height)/this->tilesHieght+1;
    yMax = yMax>this->height ? this->height : yMax;

    //draw layer by layers
    for (vector<vector<int>> layer : this->tiles)
    {
        for (int yV = yMin; yV<yMax && yV<(int)layer.size(); yV++)
            for (int xV = xMin; xV < xMax && xV<(int)layer.at(yV).size(); ++xV) {
                int id = layer.at(yV).at(xV);
                if (this->annimTileSet.find(id) != this->annimTileSet.end()){
                    id = this->annimTileSet[id].getFrame();
                }
                if (id != 0){
                    int y = floor(id/this->columns)*this->tilesHieght;
                    int x = ((id-1)%this->columns)*this->tilesWidth;

                    this->tileSetImage.drawSubsection(xV*16,yV*16,
                                                      this->tilesWidth,this->tilesHieght,
                                                      x,
                                                      y,
                                                      16,16);
                }
            }
    }

}
