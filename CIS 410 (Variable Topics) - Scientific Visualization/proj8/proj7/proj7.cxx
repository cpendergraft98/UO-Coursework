/*=========================================================================

  Program:   Visualization Toolkit
  Module:    SpecularSpheres.cxx

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
//
// This examples demonstrates the effect of specular lighting.
//
#include "vtkSmartPointer.h"
#include "vtkSphereSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkInteractorStyle.h"
#include "vtkObjectFactory.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkProperty.h"
#include "vtkCamera.h"
#include "vtkLight.h"
#include "vtkOpenGLPolyDataMapper.h"
#include "vtkJPEGReader.h"
#include "vtkImageData.h"
#include <vtkPNGWriter.h>

#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkPolyDataReader.h>
#include <vtkCleanPolyData.h>
#include <vtkPolyDataNormals.h>
#include <vtkPoints.h>
#include <vtkUnsignedCharArray.h>
#include <vtkFloatArray.h>
#include <vtkDoubleArray.h>
#include <vtkCellArray.h>
#include <vtkDataSetReader.h>
#include <vtkContourFilter.h>
#include <vtkRectilinearGrid.h>
#include <vtkDataSetWriter.h>
#include <vtkRectilinearGridToTetrahedra.h>
#include <vtkUnstructuredGrid.h>

#include <vtkCamera.h>
#include <vtkDataSetMapper.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>

#include "LUT.h"

// ****************************************************************************
//  Function: GetNumberOfPoints
//
//  Arguments:
//     dims: an array of size 3 with the number of points in X, Y, and Z.
//           2D data sets would have Z=1
//
//  Returns:  the number of points in a rectilinear mesh
//
// ****************************************************************************

int GetNumberOfPoints(const int *dims)
{
    // 3D
    return dims[0]*dims[1]*dims[2];
    // 2D
    //return dims[0]*dims[1];
}

// ****************************************************************************
//  Function: GetNumberOfCells
//
//  Arguments:
//
//      dims: an array of size 3 with the number of points in X, Y, and Z.
//            2D data sets would have Z=1
//
//  Returns:  the number of cells in a rectilinear mesh
//
// ****************************************************************************

int GetNumberOfCells(const int *dims)
{
    // 3D
    return (dims[0]-1)*(dims[1]-1)*(dims[2]-1);
    // 2D
    //return (dims[0]-1)*(dims[1]-1);
}


// ****************************************************************************
//  Function: GetPointIndex
//
//  Arguments:
//      idx:  the logical index of a point.
//              0 <= idx[0] < dims[0]
//              1 <= idx[1] < dims[1]
//              2 <= idx[2] < dims[2] (or always 0 if 2D)
//      dims: an array of size 3 with the number of points in X, Y, and Z.
//            2D data sets would have Z=1
//
//  Returns:  the point index
//
// ****************************************************************************

int GetPointIndex(const int *idx, const int *dims)
{
    // 3D
    return idx[2]*dims[0]*dims[1]+idx[1]*dims[0]+idx[0];
    // 2D
    //return idx[1]*dims[0]+idx[0];
}


// ****************************************************************************
//  Function: GetCellIndex
//
//  Arguments:
//      idx:  the logical index of a cell.
//              0 <= idx[0] < dims[0]-1
//              1 <= idx[1] < dims[1]-1 
//              2 <= idx[2] < dims[2]-1 (or always 0 if 2D)
//      dims: an array of size 3 with the number of points in X, Y, and Z.
//            2D data sets would have Z=1
//
//  Returns:  the cell index
//
// ****************************************************************************

int GetCellIndex(const int *idx, const int *dims)
{
    // 3D
    return idx[2]*(dims[0]-1)*(dims[1]-1)+idx[1]*(dims[0]-1)+idx[0];
    // 2D
    //return idx[1]*(dims[0]-1)+idx[0];
}

// ****************************************************************************
//  Function: GetLogicalPointIndex
//
//  Arguments:
//      idx (output):  the logical index of the point.
//              0 <= idx[0] < dims[0]
//              1 <= idx[1] < dims[1] 
//              2 <= idx[2] < dims[2] (or always 0 if 2D)
//      pointId:  a number between 0 and (GetNumberOfPoints(dims)-1).
//      dims: an array of size 3 with the number of points in X, Y, and Z.
//            2D data sets would have Z=1
//
//  Returns:  None (argument idx is output)
//
// ****************************************************************************

void GetLogicalPointIndex(int *idx, int pointId, const int *dims)
{
    // 3D
     idx[0] = pointId%dims[0];
     idx[1] = (pointId/dims[0])%dims[1];
     idx[2] = pointId/(dims[0]*dims[1]);

    // 2D
    // idx[0] = pointId%dims[0];
    // idx[1] = pointId/dims[0];
}


// ****************************************************************************
//  Function: GetLogicalCellIndex
//
//  Arguments:
//      idx (output):  the logical index of the cell index.
//              0 <= idx[0] < dims[0]-1
//              1 <= idx[1] < dims[1]-1 
//              2 <= idx[2] < dims[2]-1 (or always 0 if 2D)
//      cellId:  a number between 0 and (GetNumberOfCells(dims)-1).
//      dims: an array of size 3 with the number of points in X, Y, and Z.
//            2D data sets would have Z=1
//
//  Returns:  None (argument idx is output)
//
// ****************************************************************************

void GetLogicalCellIndex(int *idx, int cellId, const int *dims)
{
    // 3D
    idx[0] = cellId%(dims[0]-1);
    idx[1] = (cellId/(dims[0]-1))%(dims[1]-1);
    idx[2] = cellId/((dims[0]-1)*(dims[1]-1));

    // 2D
    //idx[0] = cellId%(dims[0]-1);
    //idx[1] = cellId/(dims[0]-1);
}


class TriangleList
{
   public:
                   TriangleList() { maxTriangles = 1000000; triangleIdx = 0; pts = new float[9*maxTriangles]; };
     virtual      ~TriangleList() { delete [] pts; };

     void          AddTriangle(float X1, float Y1, float Z1, float X2, float Y2, float Z2, float X3, float Y3, float Z3);
     vtkPolyData  *MakePolyData(void);

   protected:
     float        *pts;
     int           maxTriangles;
     int           triangleIdx;
};

void
TriangleList::AddTriangle(float X1, float Y1, float Z1, float X2, float Y2, float Z2, float X3, float Y3, float Z3)
{
    pts[9*triangleIdx+0] = X1;
    pts[9*triangleIdx+1] = Y1;
    pts[9*triangleIdx+2] = Z1;
    pts[9*triangleIdx+3] = X2;
    pts[9*triangleIdx+4] = Y2;
    pts[9*triangleIdx+5] = Z2;
    pts[9*triangleIdx+6] = X3;
    pts[9*triangleIdx+7] = Y3;
    pts[9*triangleIdx+8] = Z3;
    triangleIdx++;
}

vtkPolyData *
TriangleList::MakePolyData(void)
{
    int ntriangles = triangleIdx;
    int numPoints = 3*(ntriangles);
    vtkPoints *vtk_pts = vtkPoints::New();
    vtk_pts->SetNumberOfPoints(numPoints);
    int ptIdx = 0;
    vtkCellArray *tris = vtkCellArray::New();
    tris->EstimateSize(numPoints,4);
    for (int i = 0 ; i < ntriangles ; i++)
    {
        double pt[3];
        pt[0] = pts[9*i];
        pt[1] = pts[9*i+1];
        pt[2] = pts[9*i+2];
        vtk_pts->SetPoint(ptIdx, pt);
        pt[0] = pts[9*i+3];
        pt[1] = pts[9*i+4];
        pt[2] = pts[9*i+5];
        vtk_pts->SetPoint(ptIdx+1, pt);
        pt[0] = pts[9*i+6];
        pt[1] = pts[9*i+7];
        pt[2] = pts[9*i+8];
        vtk_pts->SetPoint(ptIdx+2, pt);
        vtkIdType ids[3] = { ptIdx, ptIdx+1, ptIdx+2 };
        tris->InsertNextCell(3, ids);
        ptIdx += 3;
    }

    vtkPolyData *pd = vtkPolyData::New();
    pd->SetPoints(vtk_pts);
    pd->SetPolys(tris);
    tris->Delete();
    vtk_pts->Delete();

    return pd;
}

int main()
{
    int  i, j;

    vtkDataSetReader *rdr = vtkDataSetReader::New();
    rdr->SetFileName("proj7.vtk");
    rdr->Update();
    if (rdr->GetOutput() == NULL || rdr->GetOutput()->GetNumberOfCells() == 0)
    {
        cerr << "Could not find input file." << endl;
        exit(EXIT_FAILURE);
    }

    vtkRectilinearGrid *rgrid = (vtkRectilinearGrid *) rdr->GetOutput();
    int dims[3];
    rgrid->GetDimensions(dims);
    float *X = (float *) rgrid->GetXCoordinates()->GetVoidPointer(0);
    float *Y = (float *) rgrid->GetYCoordinates()->GetVoidPointer(0);
    float *Z = (float *) rgrid->GetZCoordinates()->GetVoidPointer(0);
    float *F = (float *) rgrid->GetPointData()->GetScalars()->GetVoidPointer(0);

    // These were useful to me
    int edgeToVertex[12][2] =
        {
            {  0,  1 },
            {  2,  1 },
            {  2,  3 },
            {  0,  3 },
            {  4,  5 },
            {  5,  6 },
            {  6,  7 },
            {  4,  7 },
            {  0,  4 },
            {  1,  5 },
            {  3,  7 },
            {  2,  6 }
         };
    // This follows the convention in Lecture 11 slides (and project 6)
    // X is left-to-right, Y is up-and-down, Z is front-and-back.
    int offsetsI[8] = { 0, 1, 1, 0, 0, 1, 1, 0 };
    int offsetsJ[8] = { 0, 0, 0, 0, 1, 1, 1, 1 };
    int offsetsK[8] = { 0, 0, 1, 1, 0, 0, 1, 1 };

    TriangleList tl;
    int ncells = rgrid->GetNumberOfCells();
    cerr << "Number of cells to isosurface is " << ncells << endl;
    float isoval = 3.2;
    for (int cellIndex = 0 ; cellIndex < ncells ; cellIndex++)
    {
        // Find logical cell index from current cell index
        int logCellIndex[3] = { 0, 0, 0 };
        GetLogicalCellIndex(logCellIndex, cellIndex, dims);

        // Identify Cell Vertices

        // Bottom Plane, Front Left
        int v0[3] = { logCellIndex[0], logCellIndex[1], logCellIndex[2] };
        // Bottom Plane, Front Right
        int v1[3] = { v0[0]+1, v0[1], v0[2] };
        // Bottom Plane, Back Right
        int v2[3] = { v0[0]+1, v0[1], v0[2]+1 };
        // Bottom Plane, Back Left
        int v3[3] = { v0[0], v0[1], v0[2]+1 };

        // Top Plane, Front Left
        int v4[3] = { v0[0], v0[1]+1, v0[2] };
        // Top Plane, Front Right
        int v5[3] = { v0[0]+1, v0[1]+1, v0[2] };
        // Top Plane, Back Right
        int v6[3] = { v0[0]+1, v0[1]+1, v0[2]+1 };
        // Top Plane, Back Left
        int v7[3] = { v0[0], v0[1]+1, v0[2]+1 };

        // Identify Field Values
        float fv0 = F[GetPointIndex(v0, dims)];
        float fv1 = F[GetPointIndex(v1, dims)];
        float fv2 = F[GetPointIndex(v2, dims)];
        float fv3 = F[GetPointIndex(v3, dims)];
        float fv4 = F[GetPointIndex(v4, dims)];
        float fv5 = F[GetPointIndex(v5, dims)];
        float fv6 = F[GetPointIndex(v6, dims)];
        float fv7 = F[GetPointIndex(v7, dims)];

        /*          
        if (cellIndex == 4771)
        {
            cerr << "v0 = " << v0[0] <<", " << v0[1] << ", " << v0[2] << "\n";
            cerr << "ptIndex = " << GetPointIndex(v0, dims) << ", field = " << fv0 << "\n";
            cerr << "v1 = " << v1[0] <<", " << v1[1] << ", " << v1[2] << "\n";
            cerr << "ptIndex = " << GetPointIndex(v1, dims) << ", field = " << fv1 << "\n";
            cerr << "v2 = " << v2[0] <<", " << v2[1] << ", " << v2[2] << "\n";
            cerr << "ptIndex = " << GetPointIndex(v2, dims) << ", field = " << fv2 << "\n";
            cerr << "v3 = " << v3[0] <<", " << v3[1] << ", " << v3[2] << "\n";
            cerr << "ptIndex = " << GetPointIndex(v3, dims) << ", field = " << fv3 << "\n";
            cerr << "v4 = " << v4[0] <<", " << v4[1] << ", " << v4[2] << "\n";
            cerr << "ptIndex = " << GetPointIndex(v4, dims) << ", field = " << fv4 << "\n";
            cerr << "v5 = " << v5[0] <<", " << v5[1] << ", " << v5[2] << "\n";
            cerr << "ptIndex = " << GetPointIndex(v5, dims) << ", field = " << fv5 << "\n";
            cerr << "v6 = " << v6[0] <<", " << v6[1] << ", " << v6[2] << "\n";
            cerr << "ptIndex = " << GetPointIndex(v6, dims) << ", field = " << fv6 << "\n";
            cerr << "v7 = " << v7[0] <<", " << v7[1] << ", " << v7[2] << "\n";
            cerr << "ptIndex = " << GetPointIndex(v7, dims) << ", field = " << fv7 << "\n";
        }
        */
        

        int icase = 0;
        if (fv0 >= isoval)
        {
            icase += 1;
        }

        if (fv1 >= isoval)
        {
            icase += 2;
        }

        if (fv2 >= isoval)
        {
            icase += 4;
        }

        if (fv3 >= isoval)
        {
            icase += 8;
        }

        if (fv4 >= isoval)
        {
            icase += 16;
        }

        if (fv5 >= isoval)
        {
            icase += 32;
        }

        if (fv6 >= isoval)
        {
            icase += 64;
        }

        if (fv7 >= isoval)
        {
            icase += 128;
        }

        /*
        if (cellIndex == 4771){
            cerr << "Case Num = " << icase << "\n";
        }
        */

        // Stores t values as { Edge0 t val, Edge1 t val, ... ,Edge10 t val, Edge 11 t val }
        float t_array[12] = { 
            (isoval - fv0) / (fv1 - fv0),
            (isoval - fv1) / (fv2 - fv1),
            (isoval - fv2) / (fv3 - fv2),
            (isoval - fv3) / (fv0 - fv3),
            (isoval - fv4) / (fv5 - fv4),
            (isoval - fv5) / (fv6 - fv5),
            (isoval - fv6) / (fv7 - fv6),
            (isoval - fv7) / (fv4 - fv7),
            (isoval - fv0) / (fv4 - fv0),
            (isoval - fv1) / (fv5 - fv1),
            (isoval - fv3) / (fv7 - fv3),
            (isoval - fv2) / (fv6 - fv2) };

            float pt1[3] = {0, 0, 0};
            float pt2[3] = {0, 0, 0};
            float pt3[3] = {0, 0, 0};

            int i = 0;
            float t = 0.0;

        while( lookupTable[icase][i] != -1 )
        {
            int edge1 = lookupTable[icase][i];
            int edge2 = lookupTable[icase][i + 1];
            int edge3 = lookupTable[icase][i + 2];

            switch(edge1)
            {
                case 0:
                    t = t_array[0];
                    if ((t > 1) || (t < 0))
                    {
                        abort();
                    }
                    // Only changing on X axis
                    pt1[0] = X[v0[0]] + t * (X[v1[0]] - X[v0[0]]);
                    pt1[1] = Y[v0[1]]; // or Y[v1[1]]
                    pt1[2] = Z[v0[2]]; // or Z[v1[2]]
                    break;

                case 1:
                    t = t_array[1];
                    if ((t > 1) || (t < 0))
                    {
                        abort();
                    }
                    // Only changing on Z axis
                    pt1[0] = X[v1[0]]; // or X[v2[0]]
                    pt1[1] = Y[v1[1]]; // or Y[v2[1]]
                    pt1[2] = Z[v1[2]] + t * (Z[v2[2]] - Z[v1[2]]);
                    break;

                case 2:
                    t = t_array[2];
                    if ((t > 1) || (t < 0))
                    {
                        abort();
                    }
                    // Only changing on X axis
                    pt1[0] = X[v2[0]] + t * (X[v3[0]] - X[v2[0]]);
                    pt1[1] = Y[v2[1]]; // or Y[v3[1]]
                    pt1[2] = Z[v2[2]]; // or Z[v3[2]]
                    break;

                case 3:
                    t = t_array[3];
                    if ((t > 1) || (t < 0))
                    {
                        abort();
                    }
                    // Only changing on Z axis
                    pt1[0] = X[v0[0]]; // or X[v3[0]]
                    pt1[1] = Y[v0[1]]; // or Y[v3[0]]
                    pt1[2] = Z[v3[2]] + t * (Z[v0[2]] - Z[v3[2]]);
                    break;

                case 4:
                    t = t_array[4];
                    if ((t > 1) || (t < 0))
                    {
                        abort();
                    }
                    // Only changing on X axis
                    pt1[0] = X[v4[0]] + t * (X[v5[0]] - X[v4[0]]);
                    pt1[1] = Y[v4[1]]; // or Y[v5[1]]
                    pt1[2] = Z[v4[2]]; // or Z[v5[2]]
                    break;

                case 5:
                    t = t_array[5];
                    if ((t > 1) || (t < 0))
                    {
                        abort();
                    }
                    // Only changing on Z axis
                    pt1[0] = X[v5[0]]; // or X[v6[0]]
                    pt1[1] = Y[v5[1]]; // or X[v6[1]]
                    pt1[2] = Z[v5[2]] + t * (Z[v6[2]] - Z[v5[2]]);
                    break;

                case 6:
                    t = t_array[6];
                    if ((t > 1) || (t < 0))
                    {
                        abort();
                    }
                    // Only changing on X axis
                    pt1[0] = X[v6[0]] + t * (X[v7[0]] - X[v6[0]]);
                    pt1[1] = Y[v6[1]]; // or Y[v7[1]]
                    pt1[2] = Z[v6[2]]; // or Z[v7[2]]
                    break;

                case 7:
                    t = t_array[7];
                    if ((t > 1) || (t < 0))
                    {
                        abort();
                    }
                    // Only changing on the Z axis
                    pt1[0] = X[v7[0]]; // or X[v4[0]]
                    pt1[1] = Y[v7[1]]; // or Y[v4[1]]
                    pt1[2] = Z[v7[2]] + t * (Z[v4[2]] - Z[v7[2]]);
                    break;

                case 8:
                    t = t_array[8];
                    if ((t > 1) || (t < 0))
                    {
                        abort();
                    }
                    // Only changing on the Y axis
                    pt1[0] = X[v0[0]]; // or X[v4[0]] 
                    pt1[1] = Y[v0[1]] + t * (Y[v4[1]] - Y[v0[1]]);
                    pt1[2] = Z[v0[2]]; // pr Z[v4[2]]
                    break;

                case 9:
                    t = t_array[9];
                    if ((t > 1) || (t < 0))
                    {
                        abort();
                    }
                    // Only changing on the Y axis
                    pt1[0] = X[v1[0]]; // or X[v5[0]]
                    pt1[1] = Y[v1[1]] + t * (Y[v5[1]] - Y[v1[1]]);
                    pt1[2] = Z[v1[2]]; // or Z[v5[2]]
                    break;

                case 10:
                    t = t_array[10];
                    if ((t > 1) || (t < 0))
                    {
                        abort();
                    }
                    // Only changing on the Y axis
                    pt1[0] = X[v3[0]]; // or X[v7[0]]
                    pt1[1] = Y[v3[1]] + t * (Y[v7[1]] - Y[v3[1]]);
                    pt1[2] = Z[v3[2]]; // or Z[v7[2]]
                    break;

                case 11:
                    t = t_array[11];
                    if ((t > 1) || (t < 0))
                    {
                        abort();
                    }
                    // Only changing on the Y axis
                    pt1[0] = X[v2[0]]; // or X[v6[0]]
                    pt1[1] = Y[v2[1]] + t * (Y[v6[1]] - Y[v2[1]]);
                    pt1[2] = Z[v2[2]]; // or Z[v6[2]]
                    break;
            }

            switch(edge2)
            {
                case 0:
                    t = t_array[0];
                    if ((t > 1) || (t < 0))
                    {
                        abort();
                    }
                    // Only changing on X axis
                    pt2[0] = X[v0[0]] + t * (X[v1[0]] - X[v0[0]]);
                    pt2[1] = Y[v0[1]]; // or Y[v1[1]]
                    pt2[2] = Z[v0[2]]; // or Z[v1[2]]
                    break;

                case 1:
                    t = t_array[1];
                    if ((t > 1) || (t < 0))
                    {
                        abort();
                    }
                    // Only changing on Z axis
                    pt2[0] = X[v1[0]]; // or X[v2[0]]
                    pt2[1] = Y[v1[1]]; // or Y[v2[1]]
                    pt2[2] = Z[v1[2]] + t * (Z[v2[2]] - Z[v1[2]]);
                    break;

                case 2:
                    t = t_array[2];
                    if ((t > 1) || (t < 0))
                    {
                        abort();
                    }
                    // Only changing on X axis
                    pt2[0] = X[v2[0]] + t * (X[v3[0]] - X[v2[0]]);
                    pt2[1] = Y[v2[1]]; // or Y[v3[1]]
                    pt2[2] = Z[v2[2]]; // or Z[v3[2]]
                    break;

                case 3:
                    t = t_array[3];
                    if ((t > 1) || (t < 0))
                    {
                        abort();
                    }
                    // Only changing on Z axis
                    pt2[0] = X[v0[0]]; // or X[v3[0]]
                    pt2[1] = Y[v0[1]]; // or Y[v3[0]]
                    pt2[2] = Z[v3[2]] + t * (Z[v0[2]] - Z[v3[2]]);
                    break;

                case 4:
                    t = t_array[4];
                    if ((t > 1) || (t < 0))
                    {
                        abort();
                    }
                    // Only changing on X axis
                    pt2[0] = X[v4[0]] + t * (X[v5[0]] - X[v4[0]]);
                    pt2[1] = Y[v4[1]]; // or Y[v5[1]]
                    pt2[2] = Z[v4[2]]; // or Z[v5[2]]
                    break;

                case 5:
                    t = t_array[5];
                    if ((t > 1) || (t < 0))
                    {
                        abort();
                    }
                    // Only changing on Z axis
                    pt2[0] = X[v5[0]]; // or X[v6[0]]
                    pt2[1] = Y[v5[1]]; // or X[v6[1]]
                    pt2[2] = Z[v5[2]] + t * (Z[v6[2]] - Z[v5[2]]);
                    break;

                case 6:
                    t = t_array[6];
                    if ((t > 1) || (t < 0))
                    {
                        abort();
                    }
                    // Only changing on X axis
                    pt2[0] = X[v6[0]] + t * (X[v7[0]] - X[v6[0]]);
                    pt2[1] = Y[v6[1]]; // or Y[v7[1]]
                    pt2[2] = Z[v6[2]]; // or Z[v7[2]]
                    break;

                case 7:
                    t = t_array[7];
                    if ((t > 1) || (t < 0))
                    {
                        abort();
                    }
                    // Only changing on the Z axis
                    pt2[0] = X[v7[0]]; // or X[v4[0]]
                    pt2[1] = Y[v7[1]]; // or Y[v4[1]]
                    pt2[2] = Z[v7[2]] + t * (Z[v4[2]] - Z[v7[2]]);
                    break;

                case 8:
                    t = t_array[8];
                    if ((t > 1) || (t < 0))
                    {
                        abort();
                    }
                    // Only changing on the Y axis
                    pt2[0] = X[v0[0]]; // or X[v4[0]] 
                    pt2[1] = Y[v0[1]] + t * (Y[v4[1]] - Y[v0[1]]);
                    pt2[2] = Z[v0[2]]; // pr Z[v4[2]]
                    break;

                case 9:
                    t = t_array[9];
                    if ((t > 1) || (t < 0))
                    {
                        abort();
                    }
                    // Only changing on the Y axis
                    pt2[0] = X[v1[0]]; // or X[v5[0]]
                    pt2[1] = Y[v1[1]] + t * (Y[v5[1]] - Y[v1[1]]);
                    pt2[2] = Z[v1[2]]; // or Z[v5[2]]
                    break;

                case 10:
                    t = t_array[10];
                    if ((t > 1) || (t < 0))
                    {
                        abort();
                    }
                    // Only changing on the Y axis
                    pt2[0] = X[v3[0]]; // or X[v7[0]]
                    pt2[1] = Y[v3[1]] + t * (Y[v7[1]] - Y[v3[1]]);
                    pt2[2] = Z[v3[2]]; // or Z[v7[2]]
                    break;

                case 11:
                    t = t_array[11];
                    if ((t > 1) || (t < 0))
                    {
                        abort();
                    }
                    // Only changing on the Y axis
                    pt2[0] = X[v2[0]]; // or X[v6[0]]
                    pt2[1] = Y[v2[1]] + t * (Y[v6[1]] - Y[v2[1]]);
                    pt2[2] = Z[v2[2]]; // or Z[v6[2]]
                    break;

            }

            switch(edge3)
            {
                case 0:
                    t = t_array[0];
                    if ((t > 1) || (t < 0))
                    {
                        abort();
                    }
                    // Only changing on X axis
                    pt3[0] = X[v0[0]] + t * (X[v1[0]] - X[v0[0]]);
                    pt3[1] = Y[v0[1]]; // or Y[v1[1]]
                    pt3[2] = Z[v0[2]]; // or Z[v1[2]]
                    break;

                case 1:
                    t = t_array[1];
                    if ((t > 1) || (t < 0))
                    {
                        abort();
                    }
                    // Only changing on Z axis
                    pt3[0] = X[v1[0]]; // or X[v2[0]]
                    pt3[1] = Y[v1[1]]; // or Y[v2[1]]
                    pt3[2] = Z[v1[2]] + t * (Z[v2[2]] - Z[v1[2]]);
                    break;

                case 2:
                    t = t_array[2];
                    if ((t > 1) || (t < 0))
                    {
                        abort();
                    }
                    // Only changing on X axis
                    pt3[0] = X[v2[0]] + t * (X[v3[0]] - X[v2[0]]);
                    pt3[1] = Y[v2[1]]; // or Y[v3[1]]
                    pt3[2] = Z[v2[2]]; // or Z[v3[2]]
                    break;

                case 3:
                    t = t_array[3];
                    if ((t > 1) || (t < 0))
                    {
                        abort();
                    }
                    // Only changing on Z axis
                    pt3[0] = X[v0[0]]; // or X[v3[0]]
                    pt3[1] = Y[v0[1]]; // or Y[v3[0]]
                    pt3[2] = Z[v3[2]] + t * (Z[v0[2]] - Z[v3[2]]);
                    break;

                case 4:
                    t = t_array[4];
                    if ((t > 1) || (t < 0))
                    {
                        abort();
                    }
                    // Only changing on X axis
                    pt3[0] = X[v4[0]] + t * (X[v5[0]] - X[v4[0]]);
                    pt3[1] = Y[v4[1]]; // or Y[v5[1]]
                    pt3[2] = Z[v4[2]]; // or Z[v5[2]]
                    break;

                case 5:
                    t = t_array[5];
                    if ((t > 1) || (t < 0))
                    {
                        abort();
                    }
                    // Only changing on Z axis
                    pt3[0] = X[v5[0]]; // or X[v6[0]]
                    pt3[1] = Y[v5[1]]; // or X[v6[1]]
                    pt3[2] = Z[v5[2]] + t * (Z[v6[2]] - Z[v5[2]]);
                    break;

                case 6:
                    t = t_array[6];
                    if ((t > 1) || (t < 0))
                    {
                        abort();
                    }
                    // Only changing on X axis
                    pt3[0] = X[v6[0]] + t * (X[v7[0]] - X[v6[0]]);
                    pt3[1] = Y[v6[1]]; // or Y[v7[1]]
                    pt3[2] = Z[v6[2]]; // or Z[v7[2]]
                    break;

                case 7:
                    t = t_array[7];
                    if ((t > 1) || (t < 0))
                    {
                        abort();
                    }
                    // Only changing on the Z axis
                    pt3[0] = X[v7[0]]; // or X[v4[0]]
                    pt3[1] = Y[v7[1]]; // or Y[v4[1]]
                    pt3[2] = Z[v7[2]] + t * (Z[v4[2]] - Z[v7[2]]);
                    break;

                case 8:
                    t = t_array[8];
                    if ((t > 1) || (t < 0))
                    {
                        abort();
                    }
                    // Only changing on the Y axis
                    pt3[0] = X[v0[0]]; // or X[v4[0]] 
                    pt3[1] = Y[v0[1]] + t * (Y[v4[1]] - Y[v0[1]]);
                    pt3[2] = Z[v0[2]]; // pr Z[v4[2]]
                    break;

                case 9:
                    t = t_array[9];
                    if ((t > 1) || (t < 0))
                    {
                        abort();
                    }
                    // Only changing on the Y axis
                    pt3[0] = X[v1[0]]; // or X[v5[0]]
                    pt3[1] = Y[v1[1]] + t * (Y[v5[1]] - Y[v1[1]]);
                    pt3[2] = Z[v1[2]]; // or Z[v5[2]]
                    break;

                case 10:
                    t = t_array[10];
                    if ((t > 1) || (t < 0))
                    {
                        abort();
                    }
                    // Only changing on the Y axis
                    pt3[0] = X[v3[0]]; // or X[v7[0]]
                    pt3[1] = Y[v3[1]] + t * (Y[v7[1]] - Y[v3[1]]);
                    pt3[2] = Z[v3[2]]; // or Z[v7[2]]
                    break;

                case 11:
                    t = t_array[11];
                    if ((t > 1) || (t < 0))
                    {
                        abort();
                    }
                    // Only changing on the Y axis
                    pt3[0] = X[v2[0]]; // or X[v6[0]]
                    pt3[1] = Y[v2[1]] + t * (Y[v6[1]] - Y[v2[1]]);
                    pt3[2] = Z[v2[2]]; // or Z[v6[2]]
                    break;
            }
            
            i += 3;
            tl.AddTriangle(pt1[0], pt1[1], pt1[2], pt2[0], pt2[1], pt2[2], pt3[0], pt3[1], pt3[2]);
        }
    }

    vtkPolyData *pd = tl.MakePolyData();

/*
    //This can be useful for debugging
    vtkDataSetWriter *writer = vtkDataSetWriter::New();
    writer->SetFileName("proj6_out.vtk");
    writer->SetInputData(pd);
    writer->Write();
 */

    vtkCleanPolyData *cpd = vtkCleanPolyData::New();
    cpd->SetInputData(pd);
    cpd->SetAbsoluteTolerance(0);
    cpd->PointMergingOn();
    cpd->Update();
    vtkPolyDataNormals *pdn = vtkPolyDataNormals::New();
    pdn->SetInputData(cpd->GetOutput());
    //pdn->SetInputData(pd);
    pdn->Update();

    vtkSmartPointer<vtkDataSetMapper> win1Mapper =
      vtkSmartPointer<vtkDataSetMapper>::New();
    win1Mapper->SetInputData(pdn->GetOutput());
    win1Mapper->SetScalarRange(0, 0.15);

    vtkSmartPointer<vtkActor> win1Actor =
      vtkSmartPointer<vtkActor>::New();
    win1Actor->SetMapper(win1Mapper);

    vtkSmartPointer<vtkRenderer> ren1 =
      vtkSmartPointer<vtkRenderer>::New();

    vtkSmartPointer<vtkRenderWindow> renWin =
      vtkSmartPointer<vtkRenderWindow>::New();
    renWin->AddRenderer(ren1);

    vtkSmartPointer<vtkRenderWindowInteractor> iren =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
    iren->SetRenderWindow(renWin);
    ren1->AddActor(win1Actor);
    ren1->SetBackground(0.0, 0.0, 0.0);
    renWin->SetSize(800, 800);

    ren1->GetActiveCamera()->SetFocalPoint(0., 0., 0.);
    ren1->GetActiveCamera()->SetPosition(0,0,-62);
    ren1->GetActiveCamera()->SetViewUp(0,1,0);
    ren1->GetActiveCamera()->SetClippingRange(1, 100);
    //ren1->GetActiveCamera()->SetDistance(30);

    // This starts the event loop and invokes an initial render.
    //
    iren->Initialize();
    iren->Start();

    pd->Delete();
}
