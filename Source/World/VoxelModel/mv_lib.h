#ifndef __MV_LIB__
#define __MV_LIB__

// magic number
int MV_ID( int a, int b, int c, int d ) {
	return ( a ) | ( b << 8 ) | ( c << 16 ) | ( d << 24 );
}

//================
// Vec3i
//================
class MV_Vec3i {
public :
	int x = 0, y = 0, z = 0;

public :
	MV_Vec3i() {
		x = y = z = 0;
	}

	MV_Vec3i &Set( int x1, int y1, int z1 ) {
		this->x = x1;
		this->y = y1;
		this->z = z1;
		return *this;
	}

	MV_Vec3i &Zero( void ) {
		x = y = z = 0;
		return *this;
	}
};

//================
// RGBA
//================
class MV_RGBA {
public :
	unsigned char r, g, b, a;

public :
	MV_RGBA() {
		r = g = b = a = 0;
	}
};


//================
// Voxel
//================
class MV_Voxel {
public :
	unsigned char x, y, z, colorIndex;

public :
	MV_Voxel() {
		x = y = z = colorIndex = 0;
	}
};

#endif __MV_LIB__