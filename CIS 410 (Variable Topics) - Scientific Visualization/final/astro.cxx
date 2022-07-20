#include <iostream>
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
#include <cmath>
#include <vtkPNGWriter.h>

// Global variables
int w = 500;
int h = 500;
double nsamples = 256;

struct Camera
{
    double          near, far;
    double          angle;
    double          position[3];
    double          focus[3];
    double          up[3];
};


struct TransferFunction
{
    double          min;
    double          max;
    int             numBins;
    unsigned char  *colors;  // size is 3*numBins
    double         *opacities; // size is numBins

    // Take in a value and applies the transfer function.
    // Step #1: figure out which bin "value" lies in.
    // If "min" is 2 and "max" is 4, and there are 10 bins, then
    //   bin 0 = 2->2.2
    //   bin 1 = 2.2->2.4
    //   bin 2 = 2.4->2.6
    //   bin 3 = 2.6->2.8
    //   bin 4 = 2.8->3.0
    //   bin 5 = 3.0->3.2
    //   bin 6 = 3.2->3.4
    //   bin 7 = 3.4->3.6
    //   bin 8 = 3.6->3.8
    //   bin 9 = 3.8->4.0
    // and, for example, a "value" of 3.15 would return the color in bin 5
    // and the opacity at "opacities[5]".
    void ApplyTransferFunction(double value, unsigned char *RGB, double &opacity)
    {
        int bin;

        if((value < min) || (value > max))
        {
            // If no, we make it a blak space
            RGB[0] = 0;
            RGB[1] = 0;
            RGB[2] = 0;
            opacity = 0;

        }else{

            // If yes, we calculate the bin and use it to compute the colors and opacity.
            bin = (value - min) / ((max - min) / nsamples);
            opacity = opacities[bin];

            RGB[0] = colors[3*bin+0];
            RGB[1] = colors[3*bin+1];
            RGB[2] = colors[3*bin+2];
        }
    }
};

TransferFunction
SetupTransferFunction(void)
{
    int  i;

    TransferFunction rv;
    rv.min = 10;
    rv.max = 15;
    rv.numBins = 256;
    rv.colors = new unsigned char[3*256];
    rv.opacities = new double[256];
    unsigned char charOpacity[256] = {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 2, 3, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 13, 14, 14, 14, 14, 14, 14, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 5, 4, 3, 2, 3, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 17, 17, 17, 17, 17, 17, 16, 16, 15, 14, 13, 12, 11, 9, 8, 7, 6, 5, 5, 4, 3, 3, 3, 4, 5, 6, 7, 8, 9, 11, 12, 14, 16, 18, 20, 22, 24, 27, 29, 32, 35, 38, 41, 44, 47, 50, 52, 55, 58, 60, 62, 64, 66, 67, 68, 69, 70, 70, 70, 69, 68, 67, 66, 64, 62, 60, 58, 55, 52, 50, 47, 44, 41, 38, 35, 32, 29, 27, 24, 22, 20, 20, 23, 28, 33, 38, 45, 51, 59, 67, 76, 85, 95, 105, 116, 127, 138, 149, 160, 170, 180, 189, 198, 205, 212, 217, 221, 223, 224, 224, 222, 219, 214, 208, 201, 193, 184, 174, 164, 153, 142, 131, 120, 109, 99, 89, 79, 70, 62, 54, 47, 40, 35, 30, 25, 21, 17, 14, 12, 10, 8, 6, 5, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        };

    for (i = 0 ; i < 256 ; i++)
        rv.opacities[i] = charOpacity[i]/255.0;
    const int numControlPoints = 8;
    unsigned char controlPointColors[numControlPoints*3] = { 
           71, 71, 219, 0, 0, 91, 0, 255, 255, 0, 127, 0, 
           255, 255, 0, 255, 96, 0, 107, 0, 0, 224, 76, 76 
       };
    double controlPointPositions[numControlPoints] = { 0, 0.143, 0.285, 0.429, 0.571, 0.714, 0.857, 1.0 };
    for (i = 0 ; i < numControlPoints-1 ; i++)
    {
        int start = controlPointPositions[i]*rv.numBins;
        int end   = controlPointPositions[i+1]*rv.numBins+1;
std::cerr << "Working on " << i << "/" << i+1 << ", with range " << start << "/" << end << std::endl;
        if (end >= rv.numBins)
            end = rv.numBins-1;
        for (int j = start ; j <= end ; j++)
        {
            double proportion = (j/(rv.numBins-1.0)-controlPointPositions[i])/(controlPointPositions[i+1]-controlPointPositions[i]);
            if (proportion < 0 || proportion > 1.)
                continue;
            for (int k = 0 ; k < 3 ; k++)
                rv.colors[3*j+k] = proportion*(controlPointColors[3*(i+1)+k]-controlPointColors[3*i+k])
                                 + controlPointColors[3*i+k];
        }
    }    

    return rv;
}

Camera
SetupCamera(void)
{
    Camera rv;
    rv.focus[0] = 0;
    rv.focus[1] = 0;
    rv.focus[2] = 0;
    rv.up[0] = 0;
    rv.up[1] = -1;
    rv.up[2] = 0;
    rv.angle = 30;
    rv.near = 7.5e+7;
    rv.far = 1.4e+8;
    rv.position[0] = -8.25e+7;
    rv.position[1] = -3.45e+7;
    rv.position[2] = 3.35e+7;

    return rv;
}


// Helper Functions
void CalculateUandV(double *look, double *up, double *u, double *v)
{
    // Calculates vectors U and V as specified in class using our look vector
    // and our up vector. U and V are the outputs of this function.

    /*
    // Print statments for debugging
    cerr << "\n" << "Look Vector:" << "\n";
    cerr << "X: " << look[0] << ", Y: " << look[1] << ", Z: " << look[2] << "\n";
    cerr << "\n";
    
    cerr << "Up Vector:" << "\n";
    cerr << "X: " << up[0] << ", Y: " << up[1] << ", Z: " << up[2] << "\n";
    cerr << "\n";   
    */ 
    
    // First we calculate the cross product of look vector and our up vector
    double look_x_up[3];
    look_x_up[0] = (( look[1] * up[2] ) - ( look[2] * up[1] ));
    look_x_up[1] = (( look[2] * up[0] ) - ( look[0] * up[2] ));
    look_x_up[2] = (( look[0] * up[1] ) - ( look[1] * up[0] ));

    /*
    // Print statments for debugging
    cerr << "LookXUp Vector:" << "\n";
    cerr << "X: " << look_x_up[0] << ", Y: " << look_x_up[1] << ", Z: " << look_x_up[2] << "\n";
    cerr << "\n";
    */
    
    // Calculate the magintude of our previous cross product
    double mag_look_x_up = sqrt( pow(look_x_up[0], 2)  + pow(look_x_up[1], 2) + pow(look_x_up[2], 2) );

    /*
    // Print statements for debugging
    cerr << "Magnitude of LookXUp = " << mag_look_x_up << "\n";
    cerr << "\n";
    */

    // Use look_x_up and its magnitude to calculate U
    u[0] = look_x_up[0] / mag_look_x_up;
    u[1] = look_x_up[1] / mag_look_x_up;
    u[2] = look_x_up[2] / mag_look_x_up;

    // Now, using the look vector and the u vector we calculate the v vector 
    double look_x_u[3];
    look_x_u[0] = (( look[1] * u[2] ) - ( look[2] * u[1] ));
    look_x_u[1] = (( look[2] * u[0] ) - ( look[0] * u[2] ));
    look_x_u[2] = (( look[0] * u[1] ) - ( look[1] * u[0] ));

    /*
    cerr << "LookXU Vector:" << "\n";
    cerr << "X: " << look_x_u[0] << ", Y: " << look_x_u[1] << ", Z: " << look_x_u[2] << "\n";
    cerr << "\n";
    */

    // Calculate the magnitude of our preivous cross product
    double mag_look_x_u = sqrt( pow(look_x_u[0], 2)  + pow(look_x_u[1], 2) + pow(look_x_u[2], 2) );

    /*
    cerr << "Magnitude of LookXU = " << mag_look_x_u << "\n";
    cerr << "\n";
    */

    // Finally, use look_x_u and its magnitude to calculate V
    v[0] = look_x_u[0] / mag_look_x_u;
    v[1] = look_x_u[1] / mag_look_x_u;
    v[2] = look_x_u[2] / mag_look_x_u;

}

// Three dimensional pt -> pt index
int GetPointIndex(const int *idx, const int *dims)
{
    return idx[2]*dims[0]*dims[1]+idx[1]*dims[0]+idx[0];
}

// A three dimensional version of the evaluate field function I wrote in project three
// that uses the location of a known point in a cell to determine all the verticies and 
// uses the field values of those verticies to interpolate the field value at the input
// point.
float EvaluateFieldAtLocation(const double *pt, const int *dims, const float *X,
                                const float *Y, const float *Z, const float *F)
{

    // Uses the vertex layout convention from project 7
    // Bottom Plane, Front Left
    int v0[3];
    // Bottom Plane, Front Right
    int v1[3];
    // Bottom Plane, Back Right
    int v2[3];
    // Bottom Plane, Back Left
    int v3[3];
    // Top Plane, Front Left
    int v4[3];
    // Top Plane, Front Right
    int v5[3];
    // Top Plane, Back Right
    int v6[3];
    // Top Plane, Back Left
    int v7[3];

    int i = 0; 
    int j = 0; 
    int k = 0;

    for (i; i < dims[0]; i++)
    {
        if (pt[0] >= X[i] && pt[0] <= X[i+1])
        {
            break;
        }
    }

    for (j; j < dims[1]; j++)
    {
        if(pt[1] >= Y[j] && pt[1] <= Y[j+1])
        {
            break;
        }
    }

    for (k; k < dims[2]; k++)
    {
        if(pt[2] >= Z[k] && pt[2] <= Z[k+1])
        {
            break;
        }
    }

    if(i == dims[0] or j == dims[1] or k == dims[2])
    {
        return 0;
    }

    v0[0] = i;
    v1[0] = i+1;
    v2[0] = i+1;
    v3[0] = i;
    v4[0] = i;
    v5[0] = i+1;
    v6[0] = i+1;
    v7[0] = i;

    v0[1] = j;
    v1[1] = j;
    v2[1] = j;
    v3[1] = j;
    v4[1] = j+1;
    v5[1] = j+1;
    v6[1] = j+1;
    v7[1] = j+1;

    v0[2] = k;
    v1[2] = k;
    v2[2] = k+1;
    v3[2] = k+1;
    v4[2] = k;
    v5[2] = k;
    v6[2] = k+1;
    v7[2] = k+1;

    /*
    // Print statments for debugging
    cerr << "\n" << "V0:" << "\n";
    cerr << "X: " << v0[0] << ", Y: " << v0[1] << ", Z: " << v0[2] << "\n";
    cerr << "\n";
    cerr << "\n" << "V7:" << "\n";
    cerr << "X: " << v7[0] << ", Y: " << v7[1] << ", Z: " << v7[2] << "\n";
    cerr << "\n";
    */
    
    // Point indicies
    int pind_v0 = GetPointIndex(v0, dims);
    int pind_v1 = GetPointIndex(v1, dims);
    int pind_v2 = GetPointIndex(v2, dims);
    int pind_v3 = GetPointIndex(v3, dims);
    int pind_v4 = GetPointIndex(v4, dims);
    int pind_v5 = GetPointIndex(v5, dims);
    int pind_v6 = GetPointIndex(v6, dims);
    int pind_v7 = GetPointIndex(v7, dims);

    /*
    cerr << "V0 Idx: " << pind_v0 << "\n";
    cerr << "V1 Idx: " << pind_v1 << "\n";
    cerr << "V2 Idx: " << pind_v2 << "\n";
    cerr << "V3 Idx: " << pind_v3 << "\n";
    cerr << "V4 Idx: " << pind_v4 << "\n";
    cerr << "V5 Idx: " << pind_v5 << "\n";
    cerr << "V6 Idx: " << pind_v6 << "\n";
    cerr << "V7 Idx: " << pind_v7 << "\n";
    */

    // Identify Field Values
    float fv0 = F[pind_v0];
    float fv1 = F[pind_v1];
    float fv2 = F[pind_v2];
    float fv3 = F[pind_v3];
    float fv4 = F[pind_v4];
    float fv5 = F[pind_v5];
    float fv6 = F[pind_v6];
    float fv7 = F[pind_v7];

    // Calculate T values
    float xt = (pt[0] - X[v0[0]]) / (X[v5[0]] - X[v0[0]]);

    float yt = (pt[1] - Y[v0[1]]) / (Y[v5[1]] - Y[v0[1]]);

    float zt = (pt[2] - Z[v0[2]]) / (Z[v7[2]] - Z[v0[2]]);

    // Interpolate v0 to v1
    float interp1 = fv0 + xt * (fv1 - fv0);

    // Interpolate v4 to v5
    float interp2 = fv4 + xt * (fv5 - fv4);

    // Interpolate along y axis between previous two interpolations
    float interp3 = interp1 + yt * (interp2 - interp1);

    // Interpolate v3 to v2
    float interp4 = fv3 + xt * (fv2 - fv3);

    // Interpolate v7 to v6
    float interp5 = fv7 + xt * (fv6 - fv7);

    // Interpolate along y axis between previous two interpolations
    float interp6 = interp4 + yt * (interp5 - interp4);

    // Interpolate along z axis between two y interpolations
    float interp7 = interp3 + zt * (interp6 - interp3);

    return interp7;

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
    image->AllocateScalars(VTK_UNSIGNED_CHAR, 3);
    return image;
}

int main()
{
    // Initialize transfer function and camera
    TransferFunction tf = SetupTransferFunction();
    Camera c = SetupCamera();

    double ray_orig[3];
    ray_orig[0] = c.position[0];
    ray_orig[1] = c.position[1];
    ray_orig[2] = c.position[2];

     /*
    cerr << "Ray Origin:" << "\n";
    cerr << "X: " << ray_orig[0] << ", Y: " << ray_orig[1] << ", Z: " << ray_orig[2] << "\n";
    cer << "\n";
    */

    // Taken from project 3
    vtkDataSetReader *rdr = vtkDataSetReader::New();
    rdr->SetFileName("astro512.vtk");
    rdr->Update();

    // Initialize dimensions
    int dims[3];
    vtkRectilinearGrid *rgrid = (vtkRectilinearGrid *) rdr->GetOutput();
    rgrid->GetDimensions(dims);

    // Initialize X, Y, Z, and F lists
    float *X = (float *) rgrid->GetXCoordinates()->GetVoidPointer(0);
    float *Y = (float *) rgrid->GetYCoordinates()->GetVoidPointer(0);
    float *Z = (float *) rgrid->GetZCoordinates()->GetVoidPointer(0);
    float *F = (float *) rgrid->GetPointData()->GetScalars()->GetVoidPointer(0);

    vtkImageData *image = NewImage(w, h);
    unsigned char *pixel;
 
    // Step Size calculation
    double stepSize = (c.far - c.near) / (nsamples - 1);

    /*
    cerr << "StepSize: " << stepSize << "\n";
    cerr << "\n";
    */

    // Create arrays to hold U and V
    double u[3];
    double v[3];

    // Determine Look vector
    double look[3];
    look[0] = c.focus[0] - c.position[0];
    look[1] = c.focus[1] - c.position[1];
    look[2] = c.focus[2] - c.position[2];

    CalculateUandV(look, c.up, u, v);
    
    /* 
    cerr << "U Vector:" << "\n";
    cerr << "X: " << u[0] << ", Y: " << u[1] << ", Z: " << u[2] << "\n";
    cerr << "\n";

    cerr << "V Vector:" << "\n";
    cerr << "X: " << v[0] << ", Y: " << v[1] << ", Z: " << v[2] << "\n";
    cerr << "\n";
    */

    // Compute the change in x and change in y
    double delta_x[3];
    double delta_y[3];

    delta_x[0] = ((2*tan(c.angle*(M_PI/180) / 2)) / w) * u[0];
    delta_x[1] = ((2*tan(c.angle*(M_PI/180) / 2)) / w) * u[1];
    delta_x[2] = ((2*tan(c.angle*(M_PI/180) / 2)) / w) * u[2];

    delta_y[0] = ((2*tan(c.angle*(M_PI/180) / 2)) / h) * v[0];
    delta_y[1] = ((2*tan(c.angle*(M_PI/180) / 2)) / h) * v[1];
    delta_y[2] = ((2*tan(c.angle*(M_PI/180) / 2)) / h) * v[2];

    /*
    // Print statements for debugging
    cerr << "Delta X:" << "\n";
    cerr << "X: " << delta_x[0] << ", Y: " << delta_x[1] << ", Z: " << delta_x[2] << "\n";
    cerr << "\n";

    cerr << "Delta Y:" << "\n";
    cerr << "X: " << delta_y[0] << ", Y: " << delta_y[1] << ", Z: " << delta_y[2] << "\n";
    cerr << "\n";
    */

    // Compute the magnitude of our look vector for use in computing rays
    double look_mag = sqrt( pow(look[0], 2)  + pow(look[1], 2) + pow(look[2], 2) );
    
    /*
    // Print statment for debugging
    cerr << "Look Magnitude: " << look_mag << "\n";
    cerr << "\n";
    */
    int counter = 0;
    // Iterate over all of our pixels
    for(int i = 0; i < w; i++)
    {
        for(int j = 0; j < h; j++)
        {   

            // Compute ray direction for each pixel
            double ray_dir[3];
            ray_dir[0] = (look[0]/look_mag) + (((2*i + 1 - w)/2) * delta_x[0]) + (((2*j + 1 - h)/2) * delta_y[0]);
            ray_dir[1] = (look[1]/look_mag) + (((2*i + 1 - w)/2) * delta_x[1]) + (((2*j + 1 - h)/2) * delta_y[1]);
            ray_dir[2] = (look[2]/look_mag) + (((2*i + 1 - w)/2) * delta_x[2]) + (((2*j + 1 - h)/2) * delta_y[2]);

            /*
            // Print statement for debugging
            cerr << "Ray Direction:" << "\n";
            cerr << "X: " << ray_dir[0] << ", Y: " << ray_dir[1] << ", Z: " << ray_dir[2] << "\n";
            cerr << "\n";
            */
            // Generate a number of samples totaling nsamples along the ray
            double total[4] = {0, 0, 0, 0};
            for(int k = 0; k < nsamples; k++)
            {
                /*
                cerr << "\n";
                cerr << "Total X = " << total[0] << " Total Y = " << total[1] << " Total Z = " << total[2] << " Total Alpha = " << total[3];
                cerr << "\n";
                */

                // Determine samples along the ray iteritively.
                double sample_pos[3];
                sample_pos[0] = c.position[0] + (ray_dir[0]*(c.near+stepSize*k));
                sample_pos[1] = c.position[1] + (ray_dir[1]*(c.near+stepSize*k));
                sample_pos[2] = c.position[2] + (ray_dir[2]*(c.near+stepSize*k));

                // Compute the field value at the intersection
                float value = EvaluateFieldAtLocation(sample_pos, dims, X, Y, Z, F);

                // Create empty values to hold transfer function output and run transfer function
                unsigned char rgb[3];
                double alpha;
                tf.ApplyTransferFunction(value, rgb, alpha);

                // Correct opacity
                double opacity = 1 - pow((1 - alpha), (500/nsamples));

                // Create a copy of the rgb array with doubles instead of unsigned chars
                double drgb[3];
                drgb[0] = double(rgb[0])*opacity;
                drgb[1] = double(rgb[1])*opacity;
                drgb[2] = double(rgb[2])*opacity;

                total[0] = total[0] + (1 - total[3])*(drgb[0])/255;
                total[1] = total[1] + (1 - total[3])*(drgb[1])/255;
                total[2] = total[2] + (1 - total[3])*(drgb[2])/255;
                total[3] = total[3] + (1 - total[3])*opacity;

                if((i == 50) && (j == 50)){
                    if((k == 16) || (k == 19) || (k == 28)){
                        //cerr << "Sample[" << k << "]:" << "\n";
                        //cerr << "Pos = " << sample_pos[0] << ", " << sample_pos[1] << ", " << sample_pos[2] << "\n";
                        //cerr << "Maps to " << drgb[0] << ", " << drgb[1] << ", " << drgb[2] << "\n";
                        //cerr << "Value = " << value << "\n";
                        //cerr << "Alpha (Uncorrected Opacity) = " << alpha << "\n";
                        //cerr << "Opacity = " << opacity << "\n";
                        //cerr << "Total R = " << total[0] << " Total G = " << total[1] << " Total B = " << total[2] << " Total Alpha = " << total[3];
                        //cerr << "\n";
                        //cerr << "Total R = " << ret[0] << " Total G = " << ret[1] << " Total B = " << ret[2] <<"\n";
                     }
                }

            }
        // Create pixel object at given i, j 
        pixel = (unsigned char *) image->GetScalarPointer(i, j, 0);
        // Assign the pixel components to the total scalar value multiplied by 256
        pixel[0] = total[0]*256;
        pixel[1] = total[1]*256;
        pixel[2] = total[2]*256;
        }
    }
    // Write the image
    WriteImage(image, "500x500_1024samp");
}
 
