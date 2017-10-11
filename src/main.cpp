
#include <iostream>
#include <vector>
#include <string>

#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>
typedef OpenMesh::PolyMesh_ArrayKernelT<>  MyTMesh;

using std::cout;
using std::endl;
using std::vector;
using std::string;

#define min(a,b) a<b?a:b
#define max(a,b) a>b?a:b

int main(int argc, const char *argv[])
{
	string fileIn, fileOut;
	float size = 2.0;
	MyTMesh::Point centerPos = MyTMesh::Point(0.0, 0.0, 0.0);
	if (argc > 1)
	{
		if (argc == 2)
		{
			fileIn = argv[1];
			fileOut = fileIn.substr(0, fileIn.find_last_of(".")) + "_.obj";
		}
		else if (argc == 6)
		{
			fileIn = argv[1];
			size = atof(argv[2]);
			centerPos[0] = atof(argv[3]);
			centerPos[1] = atof(argv[4]);
			centerPos[2] = atof(argv[5]);
			fileOut = fileIn.substr(0, fileIn.find_last_of(".")) + "_.obj";
		}
		else if (argc == 7)
		{
			fileIn = argv[1];
			size = atof(argv[2]);
			centerPos[0] = atof(argv[3]);
			centerPos[1] = atof(argv[4]);
			centerPos[2] = atof(argv[5]);
			fileOut = argv[6];
		}
		else
		{
			cout << "Wrong input! \n"
				"Usage: \n"
				"  in.obj \n"
				"  in.obj s cx cy cz \n"
				"  in.obj s cx cy cz out.obj\n";
			return 0;
		}
		
	}
	else
		fileIn = "../vase_lion_top_poly_Result12.obj";

	
	
	MyTMesh *ptr_mesh_ = new MyTMesh();
	OpenMesh::IO::read_mesh(*ptr_mesh_, fileIn);

#define MAX_FLOAT_VALUE (static_cast<float>(10e10))
#define MIN_FLOAT_VALUE	(static_cast<float>(-10e10))
	float xmax_, xmin_, ymax_, ymin_, zmax_, zmin_;

	xmax_ = ymax_ = zmax_ = MIN_FLOAT_VALUE;
	xmin_ = ymin_ = zmin_ = MAX_FLOAT_VALUE;

	for (auto it = ptr_mesh_->vertices_begin(); it != ptr_mesh_->vertices_end(); ++it)
	{
		auto vertex = it.handle();
		MyTMesh::Point point = ptr_mesh_->point(vertex);

		xmin_ = min(xmin_, point.data()[0]);
		ymin_ = min(ymin_, point.data()[1]);
		zmin_ = min(zmin_, point.data()[2]);
		xmax_ = max(xmax_, point.data()[0]);
		ymax_ = max(ymax_, point.data()[1]);
		zmax_ = max(zmax_, point.data()[2]);
	}
	float scaleX = xmax_ - xmin_;
	float scaleY = ymax_ - ymin_;
	float scaleZ = zmax_ - zmin_;
	float scaleMax;

	scaleMax = max(scaleX, scaleY);
	scaleMax = max(scaleZ, scaleMax);
	float scaleV = size / scaleMax;
	MyTMesh::Point center((xmin_ + xmax_) / 2.f, (ymin_ + ymax_) / 2.f, (zmin_ + zmax_) / 2.f);
	for (auto it = ptr_mesh_->vertices_begin(); it != ptr_mesh_->vertices_end(); ++it)
		ptr_mesh_->point(*it) = (ptr_mesh_->point(*it) - center) * scaleV;
	
	for (auto it = ptr_mesh_->vertices_begin(); it != ptr_mesh_->vertices_end(); ++it)
		ptr_mesh_->point(*it) = ptr_mesh_->point(*it) + centerPos;
	


	// write mesh to output.obj
	try
	{
		if ( !OpenMesh::IO::write_mesh(*ptr_mesh_, fileOut) )
		{
			std::cerr << "Cannot write mesh to file" << std::endl;
			return 1;
		}
	}
	catch( std::exception& x )
	{
		std::cerr << x.what() << std::endl;
		return 1;
	}

	return 0;
}
