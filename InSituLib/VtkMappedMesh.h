/**
 * \file
 * \author Lars Bilke
 * \date   2014-02-27
 * \brief  Definition of the VtkMappedMesh class.
 *
 * \copyright
 * Copyright (c) 2013, OpenGeoSys Community (http://www.opengeosys.org)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.org/project/license
 *
 */

#ifndef VTKMAPPEDMESH_H_
#define VTKMAPPEDMESH_H_

#include "MeshEnums.h"

#include <vtkObject.h>
#include <vtkMappedUnstructuredGrid.h>

class vtkGenericCell;
namespace MeshLib {
	class Element;
	class Node;
}

namespace InSituLib
{

class VtkMappedMeshImpl : public vtkObject
{
public:
	static VtkMappedMeshImpl *New();
	virtual void PrintSelf(ostream &os, vtkIndent indent);
	vtkTypeMacro(VtkMappedMeshImpl, vtkObject)

	void SetNodes(std::vector<MeshLib::Node*> const & nodes);
	void SetElements(std::vector<MeshLib::Element*> const & elements);

	// API for vtkMappedUnstructuredGrid's implementation
	vtkIdType GetNumberOfCells();
	int GetCellType(vtkIdType cellId);
	void GetCellPoints(vtkIdType cellId, vtkIdList *ptIds);
	void GetPointCells(vtkIdType ptId, vtkIdList *cellIds);
	int GetMaxCellSize();
	void GetIdsOfCellsOfType(int type, vtkIdTypeArray *array);
	int IsHomogeneous();

	// This container is read only -- these methods do nothing but print a warning.
	void Allocate(vtkIdType numCells, int extSize = 1000);
	vtkIdType InsertNextCell(int type, vtkIdList *ptIds);
	vtkIdType InsertNextCell(int type, vtkIdType npts, vtkIdType *ptIds);
	vtkIdType InsertNextCell(int type, vtkIdType npts, vtkIdType *ptIds,
	                         vtkIdType nfaces, vtkIdType *faces);
	void ReplaceCell(vtkIdType cellId, int npts, vtkIdType *pts);

protected:
	VtkMappedMeshImpl();
	~VtkMappedMeshImpl();

private:
	VtkMappedMeshImpl(const VtkMappedMeshImpl &);  // Not implemented.
	void operator=(const VtkMappedMeshImpl &); // Not implemented.

	// const MeshLib::Mesh* _mesh;
	const std::vector<MeshLib::Node*>* _nodes;
	const std::vector<MeshLib::Element*>* _elements;
	vtkIdType NumberOfCells;

	static MeshElemType VtkCellTypeToOGS(int type)
	{
		MeshElemType ogs;
		switch (type)
		{
			case 0:
				ogs = MeshElemType::INVALID;
				break;
			case VTK_LINE:
				ogs = MeshElemType::LINE;
				break;
			case VTK_TRIANGLE:
				ogs = MeshElemType::TRIANGLE;
				break;
			case VTK_QUAD:
				ogs = MeshElemType::QUAD;
				break;
			case VTK_HEXAHEDRON:
				ogs = MeshElemType::HEXAHEDRON;
				break;
			case VTK_TETRA:
				ogs = MeshElemType::TETRAHEDRON;
				break;
			case VTK_WEDGE:
				ogs = MeshElemType::PRISM;
				break;
			case VTK_PYRAMID:
				ogs = MeshElemType::PYRAMID;
				break;
		}
		return ogs;
	}
};

vtkMakeMappedUnstructuredGrid(VtkMappedMesh, VtkMappedMeshImpl)

} // end namespace

#endif // VTKMAPPEDMESH_H_
