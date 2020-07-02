#ifndef TILEMAP_H
#define TILEMAP_H


typedef enum 
{
	TILE_NONE,
	TILE_H_U,
	TILE_H_D,
	TILE_H_L,
	TILE_H_R,
	TILE_F_UD,
	TILE_F_LR,
	TILE_CROSS,
	TILE_F_UD_H_L,
	TILE_F_UD_H_R,
	TILE_F_LR_H_U,
	TILE_F_LR_H_D,
	TILE_C_LU,
	TILE_C_LD,
	TILE_C_RD,
	TILE_C_RU,
}TileType;


typedef enum
{ 
	InsertItem, 
	InsertNode,
	SelectPath,
	MakeArrow,
}Mode;




#endif // TILEMODEL_H