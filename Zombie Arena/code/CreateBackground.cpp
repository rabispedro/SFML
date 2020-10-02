#include"ZombieArena.h"

int createBackground(VertexArray& rVA, IntRect arena){
	//	Anything going on in rVA is doing to Brackground (in the Main function)
	
	//	How big is each Tile/Texture
	const int TILE_SIZE = 50;
	const int TILE_TYPES = 3;
	const int VERTS_IN_QUAD = 4;
	
	int worldWidth = (arena.width/TILE_SIZE);
	int worldHeigth = (arena.height/TILE_SIZE);
	
	//	What Type of primitive is beeing used?
	rVA.setPrimitiveType(Quads);
	
	//	Set the Size of the Vertex Array
	rVA.resize(worldWidth*worldHeigth*VERTS_IN_QUAD);
	
	//	Start at the Beginning of the Vertex Array
	int currentVertex = 0;
	
	for(int i=0; i<worldWidth; i++){
		for(int j=0; j<worldHeigth; j++){
			//	Position each Vertex in the Current Quad
			rVA[currentVertex+0].position = Vector2f((i*TILE_SIZE),(j*TILE_SIZE));
			rVA[currentVertex+1].position = Vector2f((i*TILE_SIZE)+TILE_SIZE,(j*TILE_SIZE));
			rVA[currentVertex+2].position = Vector2f((i*TILE_SIZE)+TILE_SIZE,(j*TILE_SIZE)+TILE_SIZE);
			rVA[currentVertex+3].position = Vector2f((i*TILE_SIZE),(j*TILE_SIZE)+TILE_SIZE);
			
			//	Define the Position in the Texture for the Current Quad Either Grass, Stone, Bush or Wall
			if((j == 0) || (j == worldHeigth-1) || (i == 0) || (i == worldWidth-1)){
				//	Use the Wall Texture
				rVA[currentVertex+0].texCoords = Vector2f(0, (0+TILE_TYPES*TILE_SIZE));
				rVA[currentVertex+1].texCoords = Vector2f(TILE_SIZE, (0+TILE_TYPES*TILE_SIZE));
				rVA[currentVertex+2].texCoords = Vector2f(TILE_SIZE, (TILE_SIZE+TILE_TYPES*TILE_SIZE));
				rVA[currentVertex+3].texCoords = Vector2f(0, (TILE_SIZE+TILE_TYPES*TILE_SIZE));
			}else{
				//	Use a Random Floor Texture
				srand((int)time(0)+(j*i-j));
				int mOrg = (rand()%TILE_TYPES);
				int verticalOffset = mOrg*TILE_SIZE;
				
				rVA[currentVertex+0].texCoords = Vector2f(0, 0+verticalOffset);
				rVA[currentVertex+1].texCoords = Vector2f(TILE_SIZE, 0+verticalOffset);
				rVA[currentVertex+2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE+verticalOffset);
				rVA[currentVertex+3].texCoords = Vector2f(0, TILE_SIZE+verticalOffset);
			}
			
			//	Position ready for the next four Vertices
			currentVertex += VERTS_IN_QUAD;
		}
	}
	
	return TILE_SIZE;
}
