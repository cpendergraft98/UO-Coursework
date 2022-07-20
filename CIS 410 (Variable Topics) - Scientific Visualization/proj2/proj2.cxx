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

#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkPolyDataReader.h>
#include <vtkPoints.h>
#include <vtkUnsignedCharArray.h>
#include <vtkFloatArray.h>
#include <vtkDoubleArray.h>
#include <vtkCellArray.h>
#include <vtkDataSetReader.h>
#include <vtkContourFilter.h>
#include <vtkRectilinearGrid.h>
#include <vtkFloatArray.h>


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
    //return dims[0]*dims[1]*dims[2];
    // 2D
    return dims[0]*dims[1];
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
    //return (dims[0]-1)*(dims[1]-1)*(dims[2]-1);
    // 2D
    return (dims[0]-1)*(dims[1]-1);
}


// ****************************************************************************
//  Function: GetPointIndex
//
//  Arguments:
//      idx:  the logical index of a point.
//              0 <= idx[0] < dims[0]
//              1 <= idx[1] < dims[1]
//              2 <= idx[2] < dims[2] (or always zero if 2D)
//      dims: an array of size 3 with the number of points in X, Y, and Z
//            2D data sets would have Z=1
//
//  Returns:  the point index
//
// ****************************************************************************

int GetPointIndex(const int *idx, const int *dims)
{
    // 3D
    //return idx[2]*dims[0]*dims[1]+idx[1]*dims[0]+idx[0];
    // 2D
    return idx[1]*dims[0]+idx[0];
}


// ****************************************************************************
//  Function: GetCellIndex
//
//  Arguments:
//      idx:  the logical index of a cell.
//              0 <= idx[0] < dims[0]-1
//              1 <= idx[1] < dims[1]-1 
//              2 <= idx[2] < dims[2]-1 (or always zero if 2D)
//      dims: an array of size 3 with the number of points in X, Y, and Z
//            2D data sets would have Z=1
//
//  Returns:  the cell index
//
// ****************************************************************************

int GetCellIndex(const int *idx, const int *dims)
{
    // 3D
    //return idx[2]*(dims[0]-1)*(dims[1]-1)+idx[1]*(dims[0]-1)*idx[0];
    // 2D
    return idx[1]*(dims[0]-1)+idx[0];
}

// ****************************************************************************
//  Function: GetLogicalPointIndex
//
//  Arguments:
//      idx (output):  the logical index of the point.
//              0 <= idx[0] < dims[0]
//              1 <= idx[1] < dims[1] 
//              2 <= idx[2] < dims[2] (or always zero if 2D)
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
    // idx[0] = pointId%dim[0];
    // idx[1] = (pointId/dims[0])%dims[1];
    // idx[2] = pointId/(dims[0]*dims[1]);

    // 2D
    idx[0] = pointId%dims[0];
    idx[1] = pointId/dims[0];
}


// ****************************************************************************
//  Function: GetLogicalCellIndex
//
//  Arguments:
//      idx (output):  the logical index of the cell index.
//              0 <= idx[0] < dims[0]-1
//              1 <= idx[1] < dims[1]-1 
//              2 <= idx[2] < dims[2]-1 (or always zero if 2D)
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
    // idx[0] = cellId%(dims[0]-1);
    // idx[1] = (cellId/(dims[0]-1))%(dims[1]-1);
    // idx[2] = cellId/((dims[0]-1)*(dims[1]-1));

    // 2D
    idx[0] = cellId%(dims[0]-1);
    idx[1] = cellId/(dims[0]-1);
}


// ****************************************************************************
//  Function: EvaluateFieldAtLocation
//
//  Arguments:
//     pt: a two-dimensional location
//     dims: an array of size two.  
//           The first number is the size of the array in argument X, 
//           the second the size of Y.
//     X: an array (size is specified by dims).  
//        This contains the X locations of a rectilinear mesh.
//     Y: an array (size is specified by dims).  
//        This contains the Y locations of a rectilinear mesh.
//     F: a scalar field defined on the mesh.  
//        Its size is dims[0]*dims[1].
//
//   Returns: the interpolated field value. 0 if the location is out of bounds.
//
// ****************************************************************************

float
EvaluateFieldAtLocation(const float *pt, const int *dims, 
                        const float *X, const float *Y, const float *F)
{
    int bottom_left[2] = { 0, 0 };
    int top_right[2] = { 0, 0 };
    int bottom_right[2] = { 0, 0 };
    int top_left[2] = { 0, 0 };

    for (int i = 0; i < dims[0]; i++)
    {
        if (pt[0] >= X[i] && pt[0] <= X[i+1])
        {
            bottom_left[0] = i;
            top_left[0] = i;
            top_right[0] = i+1;
            bottom_right[0] = i+1;
            break;
        }
    }

    for (int i = 0; i < dims[1]; i++)
    {
        if(pt[1] >= Y[i] && pt[1] <= Y[i+1])
        {
            bottom_left[1] = i;
            bottom_right[1] = i;
            top_right[1] = i+1;
            top_left[1] = i+1;
            break;
        }
    }

    /*

    cerr << "Bottom-Left X is " << bottom_left[0] << "\n";
    cerr << "Bottom-Left Y is " << bottom_left[1] << "\n";

    cerr << "Bottom-Right X is " << bottom_right[0] << "\n";
    cerr << "Bottom-Right Y is " << bottom_right[1] << "\n";

    cerr << "Top-Left X is " << top_left[0] << "\n";
    cerr << "Top-Left Y is " << top_left[1] << "\n";

    cerr << "Top-Right X is " << top_right[0] << "\n";
    cerr << "Top-RIght Y is " << top_right[1] << "\n";

    */

    int bl_index = GetPointIndex(bottom_left, dims);
    int br_index = GetPointIndex(bottom_right, dims);
    int tl_index = GetPointIndex(top_left, dims);
    int tr_index = GetPointIndex(top_right, dims);

    float bl_scalar = F[bl_index];
    float br_scalar = F[br_index];
    float tl_scalar = F[tl_index];
    float tr_scalar = F[tr_index];

    float xt = (pt[0] - X[bottom_left[0]]) /
     (X[top_right[0]] - X[bottom_left[0]]);

    float yt = (pt[1] - Y[bottom_left[1]]) /
     (Y[top_right[1]] - Y[bottom_left[1]]);

    /*
    
    cerr << "xt " << xt << "\n";
    cerr << "yt " << yt << "\n";

    */

    if (std::isinf(xt) || std::isinf(yt))
    {
        return 0;
    }

    float x_bottom_interpolation = bl_scalar + xt *
     (br_scalar - bl_scalar);

    float x_top_interpolation = tl_scalar + xt *
     (tr_scalar - tl_scalar);

    float final_y_interpolation = x_bottom_interpolation +
     yt * (x_top_interpolation - x_bottom_interpolation);

    return final_y_interpolation;

}



// ****************************************************************************
//  Function: AreaForCell
//
//  Arguments:
//     X: an array (size is specified by dims).  
//              This contains the X locations of a rectilinear mesh.
//     Y: an array (size is specified by dims).  
//              This contains the Y locations of a rectilinear mesh.
//     dims: an array of size two.  
//              The first number is the size of the array in argument X, 
//              the second the size of Y.
//     cellId: a cellIndex (I.e., between 0 and GetNumberOfCells(dims))
//  
//  Returns:  the area of the cell.  Each cell is a rectangle, and the
//            area of a rectangle is width*height.
//            If an invalid cell is specified, then the function should return 0.
//
// ****************************************************************************

float
AreaForCell(const float *X, const float *Y, const int *dims, int cellId)
{
    // IMPLEMENT ME!
    
    if ((cellId < 0) || (cellId > (GetNumberOfCells(dims) - 1))){
        return 0;
    }
    

    int bottom_left[2] = { 0, 0 };
    GetLogicalCellIndex(bottom_left, cellId, dims);

    int bottom_right[2] = { bottom_left[0]+1, bottom_left[1] };
    int top_left[2] = { bottom_left[0], bottom_left[1]+1 };

    /*

    //cerr << "Bottom-Left Logical Point Index X is " << bottom_left[0] << "\n";
    //cerr << "Bottom-Left Logical Point Index Y is " << bottom_left[1] << "\n";
    cerr << "Bottom-Left X Value is " << X[bottom_left[0]] << "\n";
    cerr << "Bottom-Left Y Value is " << Y[bottom_left[1]] << "\n";

    //cerr << "Bottom-Right Logical Point Index X is " << bottom_right[0] << "\n";
    //cerr << "Bottom-Right Logical Point Index Y is " << bottom_right[1] << "\n";
    cerr << "Bottom-Right X Value is " << X[bottom_right[0]] << "\n";
    cerr << "Bottom-Right Y Value is " << Y[bottom_right[1]] << "\n";

    //cerr << "Top-Left LCI X is " << top_left[0] << "\n";
    //cerr << "Top-Left LCI Y is " << top_left[1] << "\n";
    cerr << "Top-Left X Value is " << X[top_left[0]] << "\n";
    cerr << "Top-Left Y Value is " << Y[top_left[1]] << "\n";

    */

    float width = X[bottom_right[0]] - X[bottom_left[0]];
    float height = Y[top_left[1]] - Y[bottom_left[1]];

    /*

    cerr << "Width is " << width << "\n";
    cerr << "Height is " << height << "\n";

    */
    
    return width*height;
}

// ****************************************************************************
//  Function: CountNumberOfCellsWithinThreshold
//
//  Arguments:
//     X: an array (size is specified by dims).  
//              This contains the X locations of a rectilinear mesh.
//     Y: an array (size is specified by dims).  
//              This contains the Y locations of a rectilinear mesh.
//     dims: an array of size two.  
//              The first number is the size of the array in argument X, 
//              the second the size of Y.
//     F: a scalar field defined on the mesh.  Its size is dims[0]*dims[1].
//     min: the minimum range for a threshold
//     max: the maximum range for a threshold
//
//  Returns:  the number of cells within a threshold range.
//
//  Example: assume the desired threshold range is (L, H).  Consider cell C,
//    which has 4 vertices, and assume these 4 vertices have values F1, F2,
//    F3, and F4.
//    Then we define C to be within the threshold range if:
//       L <= F1 <= H  *AND*
//       L <= F2 <= H  *AND*
//       L <= F3 <= H  *AND*
//       L <= F4 <= H 
//
//   Your goal is to count the number of cells that are within the threshold
//   range. 
//
// ****************************************************************************

int
CountNumberOfCellsWithinThreshold(const float *X, const float *Y, const int *dims,
                             const float *F, float L, float H)
{
    // Implement me!
    
    int total_cells = GetNumberOfCells(dims);
    int cell_counter = 0;

    for (int i = 0; i < total_cells; i++)
    {

        int bottom_left[2] = { 0, 0 };
        GetLogicalCellIndex(bottom_left, i, dims);
        int bottom_right[2] = { bottom_left[0]+1, bottom_left[1] };
        int top_left[2] = { bottom_left[0], bottom_left[1]+1 };
        int top_right[2] = { bottom_left[0]+1, bottom_left[1]+1 };

        int bottom_left_index = GetPointIndex(bottom_left, dims);
        int bottom_right_index = GetPointIndex(bottom_right, dims);
        int top_left_index = GetPointIndex(top_left, dims);
        int top_right_index = GetPointIndex(top_right, dims);

        if((L <= F[bottom_left_index] && 
            L <= F[bottom_right_index] && 
            L <= F[top_right_index] && 
            L <= F[top_left_index]) 
            && 
            (F[bottom_left_index]) <= H && 
            F[bottom_right_index] <= H && 
            F[top_left_index] <= H && 
            F[top_right_index] <= H) 
        {

            cell_counter += 1;
        }

    }

    return cell_counter;   
    
}

int main()
{
    int  i;

    vtkDataSetReader *rdr = vtkDataSetReader::New();
    rdr->SetFileName("proj2_data.vtk");
    rdr->Update();

    int dims[3];
    vtkRectilinearGrid *rgrid = (vtkRectilinearGrid *) rdr->GetOutput();
    rgrid->GetDimensions(dims);

    float *X = (float *) rgrid->GetXCoordinates()->GetVoidPointer(0);
    float *Y = (float *) rgrid->GetYCoordinates()->GetVoidPointer(0);
    float *F = (float *) rgrid->GetPointData()->GetScalars()->GetVoidPointer(0);
    
    float ranges[10] = { -1, 1, -1, 0, 0, 1, -0.75, -0.25, 0.25, 0.75 };
    for (int i = 0 ; i < 5 ; i++)
    {
        int numCells = CountNumberOfCellsWithinThreshold(X, Y, dims, F, ranges[2*i], ranges[2*i+1]);
        cerr << "The number of cells between " << ranges[2*i] << " and " << ranges[2*i+1] << " is " << numCells << endl;
    }

    const int ncells = 5;
    int cellIds[ncells] = { 0, 50, 678, 1000, 1200 };
    for (i = 0 ; i < ncells ; i++)
    {
        float area = AreaForCell(X, Y, dims, cellIds[i]);
        cerr << "The area for cell " << cellIds[i] << " is " << area << endl;
    }

    const int npts = 10;
    float pt[npts][3] = 
         {
            {1.01119, 0.122062, 0},
            {0.862376, 1.33829, 0},
            {0.155026, 0.126123, 0},
            {0.69736, 0.0653565, 0},
            {0.2, 0.274117, 0},
            {0.893699, 1.04111, 0},
            {0.608791, -0.0533753, 0},
            {1.00543, 0.158024, 0},
            {0.384158, -0.0768977, 0},
            {0.666757, 0.60259, 0},
         };

    

    for (i = 0 ; i < npts ; i++)
    {
        float f = EvaluateFieldAtLocation(pt[i], dims, X, Y, F);
        cerr << "Evaluated field at (" << pt[i][0] <<"," << pt[i][1] << ") as "
             << f << endl;
    }
    
}




