/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkAnnotationROIRepresentation2D.h,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
///  vtkAnnotationROIRepresentation2D - a class defining the representation for the vtkSlicerBoxWidget2
///
/// This class is a concrete representation for the vtkSlicerBoxWidget2. It
/// represents a box with seven handles: one on each of the six faces, plus a
/// center handle. Through interaction with the widget, the box
/// representation can be arbitrarily positioned in the 3D space.
//
/// To use this representation, you normally use the PlaceWidget() method
/// to position the widget at a specified region in space.
//
/// .SECTION Caveats
/// This class, and vtkSlicerBoxWidget2, are second generation VTK
/// widgets. An earlier version of this functionality was defined in the
/// class vtkSlicerBoxWidget.

/// .SECTION See Also
/// vtkSlicerBoxWidget2 vtkSlicerBoxWidget


#ifndef __vtkAnnotationROIRepresentation2D_h
#define __vtkAnnotationROIRepresentation2D_h

// Annotations includes
#include "vtkAnnotationROIRepresentation.h"

class vtkLineSource;
class vtkSphereSource;
class vtkPropPicker;
class vtkProperty2D;
class vtkPolyData;
class vtkPoints;
class vtkPolyDataAlgorithm;
class vtkPointHandleRepresentation2D;
class vtkTransform;
class vtkPlanes;
class vtkBox;
class vtkDoubleArray;
class vtkMatrix4x4;

class vtkActor2D;
class vtkPolyDataMapper2D;
class vtkPlane;
class vtkTransform;
class vtkTransformPolyDataFilter;


class VTK_SLICER_ANNOTATIONS_MODULE_VTKWIDGETS_EXPORT
vtkAnnotationROIRepresentation2D
  : public vtkAnnotationROIRepresentation
{
public:
  ///
  /// Instantiate the class.
  static vtkAnnotationROIRepresentation2D *New();

  ///
  /// Standard methods for the class.
  vtkTypeMacro(vtkAnnotationROIRepresentation2D,vtkAnnotationROIRepresentation);
  void PrintSelf(ostream& os, vtkIndent indent) VTK_OVERRIDE;

  ///
  /// Get the intersecting plane;
  vtkGetObjectMacro(IntersectionPlane,vtkPlane);

  /// Get Intersection transform to 2D coordinate system
  vtkGetObjectMacro(IntersectionPlaneTransform,vtkTransform);

  virtual void GetActors2D(vtkPropCollection *actors) VTK_OVERRIDE;

  void GetIntersectionActors(vtkPropCollection *actors);

  virtual int ComputeInteractionState(int X, int Y, int modify=0) VTK_OVERRIDE;
  virtual void StartWidgetInteraction(double e[2]) VTK_OVERRIDE;
  virtual void WidgetInteraction(double e[2]) VTK_OVERRIDE;
  virtual void SetInteractionState(int state) VTK_OVERRIDE;

  ///
  /// Methods supporting, and required by, the rendering process.
  virtual void ReleaseGraphicsResources(vtkWindow*) VTK_OVERRIDE;
  virtual int RenderOpaqueGeometry(vtkViewport*) VTK_OVERRIDE;
  virtual int RenderTranslucentPolygonalGeometry(vtkViewport*) VTK_OVERRIDE;
  virtual int RenderOverlay(vtkViewport *viewport) VTK_OVERRIDE;

  virtual int HasTranslucentPolygonalGeometry() VTK_OVERRIDE;

  virtual void SizeHandles() VTK_OVERRIDE;

  vtkGetMacro(SliceIntersectionVisibility, int);
  vtkSetMacro(SliceIntersectionVisibility, int);

  vtkGetMacro(HandlesVisibility, int);
  vtkSetMacro(HandlesVisibility, int);

  virtual int HighlightHandle(vtkProp *prop) VTK_OVERRIDE;
  virtual void HighlightFace(int cellId) VTK_OVERRIDE;

  vtkSetMacro(HandleSizeInPixels,int);
  vtkGetMacro(HandleSizeInPixels,int);


  void PrintIntersections(ostream& os);

protected:
  vtkAnnotationROIRepresentation2D();
  ~vtkAnnotationROIRepresentation2D();

  // Compute intersection line of the inputIntersectionFace and the slice plane
  // It is 50x faster than computing the intersection using vtkCutter
  virtual void ComputeIntersectionLine(vtkPolyData* inputIntersectionFace, vtkPlane* inputPlane, vtkPolyData* outputIntersectionFacesIntersection);

  /// glyphs representing hot spots (e.g., handles)
  vtkActor2D          **Handle2D;
  vtkPolyDataMapper2D **HandleMapper2D;
  vtkTransformPolyDataFilter **HandleToPlaneTransformFilters;

  /// Plane/Face intersection pipelines
  vtkPlane *IntersectionPlane;
  vtkTransform *IntersectionPlaneTransform;
  vtkPolyData *IntersectionLines[6]; // intersection lines of IntersectionFaces
  vtkPolyData *IntersectionFaces[6];
  vtkTransformPolyDataFilter *IntersectionPlaneTransformFilters[6];
  vtkActor2D *IntersectionActors[6];
  vtkPolyDataMapper2D *IntersectionMappers[6];

  vtkProperty2D *HandleProperties2D[NUMBER_HANDLES];
  vtkProperty2D *SelectedHandleProperty2D;
  vtkProperty2D *SelectedFaceProperty2D;
  vtkProperty2D *DefaultFaceProperty2D;

  vtkPropPicker *HandlePicker2D;
  vtkPropPicker *LastPicker2D;
  vtkActor2D *CurrentHandle2D;

  double LastEventPosition2D[4];

  void CreateFaceIntersections();

  double ComputeHandleRadiusInWorldCoordinates(double radInPixels);

  virtual void CreateDefaultProperties() VTK_OVERRIDE;
  virtual void PositionHandles() VTK_OVERRIDE;

  int SliceIntersectionVisibility;

  double  HandleSizeInPixels;
  int HandlesVisibility;

private:
  vtkAnnotationROIRepresentation2D(const vtkAnnotationROIRepresentation2D&);  //Not implemented
  void operator=(const vtkAnnotationROIRepresentation2D&);  //Not implemented
};

#endif
