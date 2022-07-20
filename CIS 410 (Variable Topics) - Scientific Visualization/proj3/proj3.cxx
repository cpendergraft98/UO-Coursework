#include <vtkImageData.h>
#include <vtkPNGWriter.h>
#include <vtkPointData.h>
#include <vtkPoints.h>
#include <vtkUnsignedCharArray.h>
#include <vtkFloatArray.h>
#include <vtkDataSetReader.h>
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
//  Function: EvaluateFieldAtLocation
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
//     F: a scalar field defined on the mesh.  Its size is dims[0]*dims[1].
//
//   Returns: the interpolated field value. 0 if the location is out of bounds.
//
// ****************************************************************************

float EvaluateFieldAtLocation(const float *pt, const int *dims, const float *X, 
                              const float *Y, const float *F)
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

void
WriteImage(vtkImageData *img, const char *filename)
{
    std::string full_filename = filename;
    full_filename += ".png";
    vtkPNGWriter *writer = vtkPNGWriter::New();
    writer->SetInputData(img);
    writer->SetFileName(full_filename.c_str());
    writer->Write();
    writer->Delete();
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

// ****************************************************************************
//  Function: ApplyBlueHotColorMap
//
//  Purpose: 
//     Maps a normalized scalar value F (0<=F<=1) to a color using the blue 
//     hot color map.
//
//     The blue hot color map has:
//        F=0: (0,0,0.5) 
//        F=1: (1.0,1.0,1.0) 
//       and smooth interpolation in between
//
//  Arguments:
//       F (input):     a scalar value between 0 and 1
//       RGB (output):  the location to store the color
//      
//  Note: color map is in float (0 to 1) and output is in unsigned char
//        (0 to 255), so the floating point values you calculate for 
//        the three color channels need to be multiplied by 255 when
//        being assigned to RGB.
//
// ****************************************************************************

void ApplyBlueHotColorMap(float F, unsigned char *RGB)
{
    // Comments for myself for future reference.
    // If F is normalized to K, then it stands to reason that the three RGB componenets 
    // associated with F (R, G, and B) will also respectively normalize to K. Thus, we 
    // have the following 3 equations:
        //K = (R - Leftbound[R]) / (Rightbound[R] - Leftbound[R])
        //K = (G - Leftbound[G]) / (Rightbound[G] - Leftbound[G])
        //K = (B - Leftbound[B]) / (Rightbound[B] - Leftbound[B])
        // Where Leftbound[R] = R[Smaller F] and Rightbound[R] = R[Larger F]. (Same logic for B, G).
    // These equations can be re-written as:
        // R = K*(Rightbound[R] - Leftbound[R]) + Leftbound[R]
        // G = K*(Rightbound[G] - Leftbound[G]) + Leftbound[G]
        // B = K*(Rightbound[B] - Leftbound[B]) + Leftbound[B]
        // Where Leftbound[R] = R[Smaller F] and Rightbound[R] = R[Larger F]. (Same logic for B, G).
    
    // The F we are given is already normalized, so for this function F can replae K in the previous
    // equations. Use these equations to calculate RGB and then multiply by 255 when assigning.

    RGB[0] = F*255;
    RGB[1] = F*255;
    RGB[2] = (F*0.5 + 0.5)*255;

}


// ****************************************************************************
//  Function: ApplyDifferenceColorMap
//
//  Purpose: 
//     Maps a normalized scalar value F (0<=F<=1) to a color 
//     using a difference colormap.
//
//     The difference color map has:
//        F=0: (0,0,0.5) 
//        F=0.5: (1.0,1.0,1.0) 
//        F=1: (0.5, 0, 0)
//       and smooth interpolation in between
//
//  Arguments:
//       F (input):     a scalar value between 0 and 1
//       RGB (output):  the location to store the color
//      
//  Note: color map is in float (0 to 1) and output is in unsigned char
//        (0 to 255), so the floating point values you calculate for 
//        the three color channels need to be multiplied by 255 when
//        being assigned to RGB.
//
// ****************************************************************************

void ApplyDifferenceColorMap(float F, unsigned char *RGB)
{

    // Comments for myself for future reference.
    // If F is normalized to K, then it stands to reason that the three RGB componenets 
    // associated with F (R, G, and B) will also respectively normalize to K. Thus, we 
    // have the following 3 equations:
        //K = (R - Leftbound[R]) / (Rightbound[R] - Leftbound[R])
        //K = (G - Leftbound[G]) / (Rightbound[G] - Leftbound[G])
        //K = (B - Leftbound[B]) / (Rightbound[B] - Leftbound[B])
        // Where Leftbound[R] = R[Smaller F] and Rightbound[R] = R[Larger F]. (Same logic for B, G).
    // These equations can be re-written as:
        // R = K*(Rightbound[R] - Leftbound[R]) + Leftbound[R]
        // G = K*(Rightbound[G] - Leftbound[G]) + Leftbound[G]
        // B = K*(Rightbound[B] - Leftbound[B]) + Leftbound[B]
        // Where Leftbound[R] = R[Smaller F] and Rightbound[R] = R[Larger F]. (Same logic for B, G).

    // The F we are given is already normalized again, but this time we are going to need to 
    // re-normalize it for two cases: one in which 0 <= F < 0.5 and one in which 0.5 < F <= 1 as
    // in those cases our Fmin and Fmax values are no longer 0 and 1 as they were when we first 
    // normalized F. That means for this particular case that F needs to be re-normalized before it
    // can replace K in the above equations.

    if (F == 0.5)
        // We are told what RGB should be when F == 0.5
    {
        RGB[0] = 255;
        RGB[1] = 255;
        RGB[2] = 255;

    }else if (F < 0.5)
    {
        // Have to normalize F again to find normalized val bettween 0 and 0.5 bc
        // F currently normalized between 0 and 1
        float newNormF = (F - 0)/(0.5 - 0);

        RGB[0] = newNormF*255;
        RGB[1] = newNormF*255;
        RGB[2] = (newNormF*0.5 + 0.5)*255;


    }else
    {
        // Have to normalize F again to find normalized val bettween 0.5 and 1 bc
        // F currently normalized between 0 and 1

        /*
        NOTE TO SELF

        Be very careful when determining bounds! It is possible to have boundaries like
        {1.0, 0.5}, it isn't always {smaller num, bigger num}. Adhere to how you say to 
        generate left and right bounds at the top to ensure you use the right values.
        */

        float newNormF = (F - 0.5)/(1 - 0.5);

        RGB[0] = (newNormF*(0.5 - 1.0) + 1.0)*255;
        RGB[1] = (newNormF*(0 - 1.0) + 1.0)*255;
        RGB[2] = (newNormF*(0 - 1.0) + 1.0)*255;

    }
}

// ****************************************************************************
//  Function: ApplyHSVColorMap
//
//  Purpose: 
//     Maps a normalized scalar value F (0 <= F <= 1) to a color using 
//     an HSV rainbowcolormap.
//
//     The rainbow colormap uses a saturation = 1.0, value = 1.0, 
//     and interpolates hue from 0 to 360 degrees.
//
//  Arguments:
//       F (input):     a scalar value between 0 and 1  
//       RGB (output):  the location to store the color
//      
//  Note: as with the first two functions, make sure to multiple by 255 
//        when converting floats to unsigned chars.
//
// ****************************************************************************

void ApplyHSVColorMap(float F, unsigned char *RGB)  
{
    /* 
    If F normalizes to K, and the Hue value is associatd with F, then the Hue value also
    normalizes to K. Since F is already normalized:

    F = H - 0 / (360 - 0)
    H = F*360
    */
    float hue = F*360;  

    // Sat and Val provided
    float saturation = 1.0;
    float value = 1.0;

    hue /= 60.0;

    // Sector 0 to 5
    int i = std::floor(hue);
    float f = hue - i;

    // Factorial part of H 
    float p = (value * (1 - saturation)) * 255;
    float q = (value * (1 - saturation * f)) * 255;
    float t = (value * (1 - saturation * (1 - f))) * 255;

    switch(i){

        case 0:
            RGB[0] = 255;
            RGB[1] = t;
            RGB[2] = p;
            break;

        case 1:
            RGB[0] = q;
            RGB[1] = 255;
            RGB[2] = p;
            break;

        case 2:
            RGB[0] = p;
            RGB[1] = 255;
            RGB[2] = t;
            break;

        case 3:
            RGB[0] = p;
            RGB[1] = q;
            RGB[2] = 255;
            break;

        case 4:
            RGB[0] = t;
            RGB[1] = p;
            RGB[2] = 255;
            break;

        case 5:
            RGB[0] = 255;
            RGB[1] = p;
            RGB[2] = q;
            break;

    }

}


int main()
{
    int  i, j;

    vtkDataSetReader *rdr = vtkDataSetReader::New();
    rdr->SetFileName("proj3_data.vtk");
    rdr->Update();

    int dims[3];
    vtkRectilinearGrid *rgrid = (vtkRectilinearGrid *) rdr->GetOutput();
    rgrid->GetDimensions(dims);

    float *X = (float *) rgrid->GetXCoordinates()->GetVoidPointer(0);
    float *Y = (float *) rgrid->GetYCoordinates()->GetVoidPointer(0);
    float *F = (float *) rgrid->GetPointData()->GetScalars()->GetVoidPointer(0);
    
    int nx = 500;
    int ny = 500;

    vtkImageData *images[3];
    unsigned char *buffer[3];
    for (i = 0 ; i < 3 ; i++)
    {
        images[i] = NewImage(nx, ny);
        buffer[i] = (unsigned char *) images[i]->GetScalarPointer(0,0,0);
    }

    for (i = 0 ; i < 3 ; i++)
       for (j = 0 ; j < 3*nx*ny ; j++)
            buffer[i][j] = 0;

    for (i = 0 ; i < nx ; i++)
        for (j = 0 ; j < ny ; j++)
        {
            // ITERATE OVER PIXELS
            float pt[2];
            pt[0] = i / ((float)nx - 1.0)* 18.0 - 9.0;
            pt[1] = j / ((float)ny - 1.0)* 18.0 - 9.0;
            float f = EvaluateFieldAtLocation(pt, dims, X, Y, F);
            float normalizedF = (f - 1.20) / (5.02 - 1.20);
            
            // I TAKE OVER HERE
            int offset = 3*(j*nx+i);
            ApplyBlueHotColorMap(normalizedF, buffer[0]+offset);
            ApplyDifferenceColorMap(normalizedF, buffer[1]+offset);
            ApplyHSVColorMap(normalizedF, buffer[2]+offset);
        }

    WriteImage(images[0], "bluehot");
    WriteImage(images[1], "difference");
    WriteImage(images[2], "hsv");
}
