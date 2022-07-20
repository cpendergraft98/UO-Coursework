#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkDataSetReader.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkLookupTable.h>
#include <vtkContourFilter.h>
#include <vtkPlane.h>
#include <vtkCutter.h>
#include <vtkCamera.h>


int main(int argc, char *argv[])
{
   vtkDataSetReader *reader = vtkDataSetReader::New();
   reader->SetFileName("noise.vtk");
   reader->Update();



   vtkPlane *plane = vtkPlane::New();
   plane->SetNormal(0,0,1);

   vtkCutter *cutter = vtkCutter::New();
   cutter->SetCutFunction(plane);
   cutter->SetInputConnection(reader->GetOutputPort());
   cutter->Update();

   double isoval = 1.0;
   vtkContourFilter *cf = vtkContourFilter::New();
   cf->SetNumberOfContours(2);
   cf->SetValue(0, isoval);
   cf->SetValue(1, isoval);
   cf->SetInputConnection(reader->GetOutputPort());

   vtkDataSetMapper *mapper1 = vtkDataSetMapper::New();
   mapper1->SetInputConnection(cutter->GetOutputPort());
   vtkDataSetMapper *mapper2 = vtkDataSetMapper::New();
   mapper2->SetInputConnection(cf->GetOutputPort());
   
   vtkLookupTable *lut = vtkLookupTable::New();
   mapper1->SetLookupTable(lut);
   mapper1->SetScalarRange(1,6);
   mapper2->SetLookupTable(lut);
   mapper2->SetScalarRange(1,6);
   lut->Build();

   for(int i = 0; i < 256; i++)
   {
      lut->SetTableValue(i, i, 0.0, 256.0 - i, 1.0);
   }

   vtkActor *actor1 = vtkActor::New();
   actor1->SetMapper(mapper1);
   vtkActor *actor2 = vtkActor::New();
   actor2->SetMapper(mapper2);

   vtkRenderer *ren1 = vtkRenderer::New();
   ren1->AddActor(actor1);
   vtkRenderer *ren2 = vtkRenderer::New();
   ren2->AddActor(actor2);

   vtkRenderWindow *renwin = vtkRenderWindow::New();
   renwin->AddRenderer(ren1);
   renwin->AddRenderer(ren2);

   ren1->SetViewport(0.0, 0.0, 0.5, 1.0);
   ren2->SetViewport(0.5, 0.0, 1.0, 1.0);
   renwin->SetSize(768, 768);

   vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
   iren->SetRenderWindow(renwin);
   renwin->Render();

   for(int i = 0; i < 250; i++)
   {
      // I couldn't decide if we were to keep using 2 contours as we have been or if we should use 1, so I just defaulted to the convention we have
      // been using the whole time and just use two contours. I tried to set it up such that when our isoval is 4 our first contour has 
      // isoval/1.667 ~ 2.4 and our second contour has isoval 4, like it was when we hardcoded the contours. In any case I think I have demonstrated
      // that I figured out the animation. 

      // Also, on the hint for 8G you say we should stop after 500 iterations, but if we did 500 iterations with an increase of 0.02 each time we
      // would end up with isovals in the range 1->12 instead of 1->6 which is what you specify in the instructions, so I am assuming that the 
      // 500 iterations bit is a typo and is meant to be 250.
      cf->Update();
      cf->SetValue(0, isoval/1.667); // When isoval = 4, isoval/1.667 ~ 2.4.
      cf->SetValue(1, isoval);
      cf->Update();

      isoval += 0.02;

      ren2->GetActiveCamera()->ShallowCopy(ren1->GetActiveCamera());
      renwin->Render();
   }

   iren->Start();
}


