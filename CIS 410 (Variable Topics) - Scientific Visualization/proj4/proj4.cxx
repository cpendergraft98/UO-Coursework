#include <vtkImageData.h>
#include <vtkPNGWriter.h>
#include <vtkPointData.h>
#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkUnsignedCharArray.h>
#include <vtkFloatArray.h>
#include <vtkDataSetReader.h>
#include <vtkRectilinearGrid.h>
#include <vtkFloatArray.h>
#include <vtkPolyData.h>
#include <vtkDataSetWriter.h>
#include <vtkTubeFilter.h>
#include <vtkPolyDataNormals.h>
#include <vtkSphereSource.h>

#include <vtkCamera.h>
#include <vtkDataSetMapper.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>

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
    //return idx[2]*(dims[0]-1)*(dims[1]-1)+idx[1]*(dims[0]-1)+idx[0];
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
    // idx[0] = cellId%(dims[0]-1);
    // idx[1] = (cellId/(dims[0]-1))%(dims[1]-1);
    // idx[2] = cellId/((dims[0]-1)*(dims[1]-1));

    // 2D
    idx[0] = cellId%(dims[0]-1);
    idx[1] = cellId/(dims[0]-1);
}


// ****************************************************************************
//  Function: EvaluateVectorFieldAtLocation
//
//  Arguments:
//     pt: a two-dimensional location
//     dims: an array of size two.  
//              The first number is the size of the array in argument X, 
//              the second the size of Y.
//     X: an array (size is specified by dims).  
//              This contains the X locations of a rectilinear mesh.
//     Y: an array (size is specified by dims).  
//              This contains the Y locations of a rectilinear mesh.
//     F: a vector field defined on the mesh.  Its size is 2*dims[0]*dims[1].
//        The first value in the field is the x-component for the first point.
//        The second value in the field is the y-component for the first point.
//
//     rv (output): the interpolated field value. (0,0) if the location is out of bounds.
//
// ****************************************************************************

void EvaluateVectorFieldAtLocation(const float *pt, const int *dims, const float *X, 
                              const float *Y, const float *F, float *rv)
{

    rv[0] = 0;
    rv[1] = 0;
 
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
       Our F list has twice as many values as our list of point indices and is structured as { x, y, x, y, ...}.
       This means that point index 0 has vector { F[0], F[1] }, point index 1 has vector { F[2], F[3] }, point 
       index 2 has vector { F[4], F[5] }. The X component index is always 2*point index, and the Y componenet is always
       2*point index + 1, so we mutliply our point index by 2 so we know that we are always looking at the X componenet
       of the vector associated with the point index and the Y component is 1 index to the right.
    */

    int bl_index = GetPointIndex(bottom_left, dims) * 2;
    int br_index = GetPointIndex(bottom_right, dims) * 2;
    int tl_index = GetPointIndex(top_left, dims) * 2;
    int tr_index = GetPointIndex(top_right, dims) * 2;

    float bl_vector[2] = { F[bl_index], F[bl_index+1] };
    float br_vector[2] = { F[br_index], F[br_index+1] };
    float tl_vector[2] = { F[tl_index], F[tl_index+1] };
    float tr_vector[2] = { F[tr_index], F[tr_index+1] };

    float xt = (pt[0] - X[bottom_left[0]]) /
     (X[top_right[0]] - X[bottom_left[0]]);

    float yt = (pt[1] - Y[bottom_left[1]]) /
     (Y[top_right[1]] - Y[bottom_left[1]]);

    if (!(std::isinf(xt) || std::isinf(yt)))
    {
        float x_bottom_interpolation[2] = { 0, 0 };
        float x_top_interpolation[2] = { 0, 0 };

        x_bottom_interpolation[0] = bl_vector[0] + xt *
         (br_vector[0] - bl_vector[0]);
        x_bottom_interpolation[1] = bl_vector[1] + xt *
         (br_vector[1] - bl_vector[1]);


        x_top_interpolation[0] = tl_vector[0] + xt *
         (tr_vector[0] - tl_vector[0]);
        x_top_interpolation[1] = tl_vector[1] + xt *
         (tr_vector[1] - tl_vector[1]);


        rv[0] = x_bottom_interpolation[0] +
         yt * (x_top_interpolation[0] - x_bottom_interpolation[0]);
        rv[1] = x_bottom_interpolation[1] +
         yt * (x_top_interpolation[1] - x_bottom_interpolation[1]);
    }

}

// ****************************************************************************
//  Function: AdvectWithEulerStep
//
//  Arguments:
//     pt: the seed location (two-dimensions)
//     dims: an array of size two.  
//              The first number is the size of the array in argument X, 
//              the second the size of Y.
//     X: an array (size is specified by dims).  
//              This contains the X locations of a rectilinear mesh.
//     Y: an array (size is specified by dims).  
//              This contains the Y locations of a rectilinear mesh.
//     F: a vector field defined on the mesh.  Its size is 2*dims[0]*dims[1].
//     h: The size of the Euler step
//     nsteps: The number of Euler steps to take
//     output_locations (output): An array of size 2*(nsteps+1).  It's first entry
//        should be the seed location.  The second entry should be the result
//        of the first advection step.  The final entry should be the result
//        of the final advection step.
//
// ****************************************************************************

void
AdvectWithEulerStep(const float *pt, const int *dims, const float *X, 
                    const float *Y, const float *F, 
                    float h, int nsteps, float *output_locations)
{
    output_locations[0] = pt[0]; // set the x component of the first output location
    output_locations[1] = pt[1]; // set the y component of the first output location

    for (int i = 2; i < (nsteps+1)*2; i += 2)
    {
        float prev_pt[2] = { output_locations[i - 2], output_locations[i - 2 + 1] };
        float prev_pt_vector[2] = { 0, 0 };

        EvaluateVectorFieldAtLocation(prev_pt, dims, X, Y, F, prev_pt_vector);

        output_locations[i] = output_locations[i - 2] + h * prev_pt_vector[0];
        output_locations[i+1] = output_locations[i - 2 + 1] + h * prev_pt_vector[1];
    }
}

void
AdvectWithRK4Step(const float *pt, const int *dims, const float *X, 
                    const float *Y, const float *F, 
                    float h, int nsteps, float *rk4_output_locations)
{
    rk4_output_locations[0] = pt[0]; // set the x component of the first output location
    rk4_output_locations[1] = pt[1]; // set the y component of the first output location

    for (int i = 2; i < (nsteps+1)*2; i += 2)
    {
        
        float k1[2] = { 0, 0 };
        float k1_pt[2] = { rk4_output_locations[i - 2], rk4_output_locations[i - 2 + 1] };
        EvaluateVectorFieldAtLocation(k1_pt, dims, X, Y, F, k1);

        float k2[2] = { 0, 0 };
        float k2_pt[2] = { rk4_output_locations[i - 2] + (h/2)*k1[0], rk4_output_locations[i - 2 + 1] + (h/2)*k1[1] };
        EvaluateVectorFieldAtLocation(k2_pt, dims, X, Y, F, k2);

        float k3[2] = { 0, 0 };
        float k3_pt[2] = { rk4_output_locations[i - 2] + (h/2)*k2[0], rk4_output_locations[i - 2 + 1] + (h/2)*k2[1] };
        EvaluateVectorFieldAtLocation(k3_pt, dims, X, Y, F, k3);

        float k4[2] = { 0, 0 };
        float k4_pt[2] = { rk4_output_locations[i - 2] + h*k3[0], rk4_output_locations[i - 2 + 1] + h*k3[1] };
        EvaluateVectorFieldAtLocation(k4_pt, dims, X, Y, F, k4);

        rk4_output_locations[i] = rk4_output_locations[i - 2] + ((1.0)/(6.0)) * h
         * (k1[0] + 2*k2[0] + 2*k3[0] + k4[0]);
        rk4_output_locations[i+1] = rk4_output_locations[i - 2 + 1] + ((1.0)/(6.0)) * h
         * (k1[1] + 2*k2[1] + 2*k3[1] + k4[1]);
    }
}

vtkImageData *
NewImage(int width, int height)
{
    vtkImageData *image = vtkImageData::New();
    image->SetDimensions(width, height, 1);
    //image->SetWholeExtent(0, width-1, 0, height-1, 0, 0);
    //image->SetUpdateExtent(0, width-1, 0, height-1, 0, 0);
    //image->SetNumberOfScalarComponents(3);
    image->AllocateScalars(VTK_UNSIGNED_CHAR, 3);
    //image->AllocateScalars();

    return image;
}

// VTK files are only 3D, so the vector data is all of the form (X,Y,0).
// Remove the 0's since it is counter-intuitive for students who are 
// thinking of this as 2D data.
float *
Convert3DVectorDataTo2DVectorData(const int *dims, const float *F)
{
    float *rv = new float[dims[0]*dims[1]*2];
    int index3D = 0;
    int index2D = 0;
    for (int i = 0 ; i < dims[0] ; i++)
       for (int j = 0 ; j < dims[1] ; j++)
       {
           rv[index2D]   = F[index3D];
           rv[index2D+1] = F[index3D+1];
           index2D += 2;
           index3D += 3;
       }

    return rv;
}

void PrintSteps(const char *solver, int nsteps, float *locations)
{
   cerr << "Printing output for solver " << solver << endl;
   for (int j = 0 ; j < nsteps+1 ; j++)
   {
       cerr << j << ": (" << locations[2*j] << ", " << locations[2*j+1] << ")" << endl;
   }
}

int main()
{
    int  i, j;

    // HANK'S CODE TO SET THINGS UP -- DON'T MODIFY THIS
    vtkDataSetReader *rdr = vtkDataSetReader::New();
    rdr->SetFileName("proj4_data.vtk");
    rdr->Update();

    int dims[3];
    vtkRectilinearGrid *rgrid = (vtkRectilinearGrid *) rdr->GetOutput();
    rgrid->GetDimensions(dims);

    if (dims[0] <= 0 || dims[1] <= 0)
    {
        cerr << "Was not able to successfully open file \"proj4_data.vtk\"" << endl;
        exit(EXIT_FAILURE);
    }
    float *X = (float *) rgrid->GetXCoordinates()->GetVoidPointer(0);
    float *Y = (float *) rgrid->GetYCoordinates()->GetVoidPointer(0);
    float *F_3D = (float *) rgrid->GetPointData()->GetVectors()->GetVoidPointer(0);
    float *F = Convert3DVectorDataTo2DVectorData(dims, F_3D);
    
    float seed[2] = { 1, -5 };
    
    // SANITY CHECK TO MAKE SURE VECTOR FIELD EVALUATION IS WORKING
    float vec[2];
    EvaluateVectorFieldAtLocation(seed, dims, X, Y, F, vec);
    cerr << "Velocity at (" << seed[0] <<", " << seed[1] << ") is (" << vec[0] << ", " << vec[1] << ")" << endl;

    float h = 0.01;
    const int nsteps = 100;
    float *output_locations = new float[2*(nsteps+1)];
    AdvectWithEulerStep(seed, dims, X, Y, F, h, nsteps, output_locations);
    PrintSteps("Euler", nsteps, output_locations);

   float *RK4_output_locations = new float[2*(nsteps+1)];
   AdvectWithRK4Step(seed, dims, X, Y, F, h, nsteps, RK4_output_locations);
   PrintSteps("RK4", nsteps, RK4_output_locations);
}
