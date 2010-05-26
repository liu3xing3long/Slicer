///  vtkMeasurementsGUI
/// 
/// Slicer Welcome and Overview


#ifndef __vtkMeasurementsGUI_h
#define __vtkMeasurementsGUI_h

#include "vtkMeasurementsWin32Header.h"
#include "vtkSlicerModuleGUI.h"
#include "vtkMeasurementsLogic.h"
#include "vtkSlicerModuleCollapsibleFrame.h"
#include <string>

class vtkKWFrame;
class vtkKWCheckButton;
class vtkAffineWidget;
class vtkAffineRepresentation2D;
class vtkSlicerNodeSelectorWidget;
class vtkMeasurementsRulerWidget;
class vtkMeasurementsAngleWidget;
class VTK_MEASUREMENTS_EXPORT vtkMeasurementsGUI : public vtkSlicerModuleGUI
{
  public:
  static vtkMeasurementsGUI *New();
  vtkTypeRevisionMacro(vtkMeasurementsGUI,vtkSlicerModuleGUI);
  void PrintSelf(ostream& os, vtkIndent indent);

  /// 
  /// Set the logic pointer from parent class pointer.
  /// Overloads implementation in vtkSlicerModulesGUI
  /// to allow loadable modules.
  virtual void SetModuleLogic ( vtkSlicerLogic *logic )
  {
  this->SetLogic(reinterpret_cast<vtkMeasurementsLogic*> (logic)); 
  };

   ///  Get/Set logic
  vtkGetObjectMacro (Logic, vtkMeasurementsLogic);
  vtkSetObjectMacro (Logic, vtkMeasurementsLogic);

  /// 
  /// Create widgets

  virtual void BuildGUI ( );
  //BTX
  using vtkSlicerComponentGUI::BuildGUI;
  //ETX
  virtual void TearDownGUI ( );
  vtkIntArray *NewObservableEvents();

  /// 
  /// Add obsereves to GUI widgets
  virtual void AddGUIObservers ( );

  /// 
  /// Remove obsereves to GUI widgets
  virtual void RemoveGUIObservers ( );
  
  /// 
  /// Pprocess events generated by GUI widgets
  virtual void ProcessGUIEvents ( vtkObject *caller, unsigned long event,
                                  void *callData );

  ///
  /// Process events generated by mrml
  virtual void ProcessMRMLEvents ( vtkObject *caller, unsigned long event, void *callData );

  /// 
  /// Describe behavior at module startup and exit.
  virtual void Enter ( );
  //BTX
  using vtkSlicerComponentGUI::Enter;
  //ETX
  virtual void Exit ( );
  virtual void Init ( );

  /// 
  /// Access widgets
  vtkGetObjectMacro(RulerWidget, vtkMeasurementsRulerWidget);
  vtkGetObjectMacro(AngleWidget, vtkMeasurementsAngleWidget);

  /// 
  /// assign the mrml node that's selected in the TransformableNodeSelectorWidget to the TransformWidget to be manipulated via it's transform node 
  void UpdateTransformableNode();

  ///
  /// Update the vtk 3d widget from the input node, called when the transform
  /// on the node is modified
  void Update3DWidget(vtkMRMLTransformableNode *node);

  /// 
  /// update the viewer widget on the sub widgets
  void SetActiveViewer(vtkSlicerViewerWidget *activeViewer );

  ///
  /// make sure that remove any observes on transformable nodes in the scene
  void RemoveMRMLObservers ( );

  ///
  /// modify locks on all 3d widgets for which this module is responsible
  void ModifyAllLock(int lockFlag);
  
protected:
  vtkMeasurementsGUI();
  ~vtkMeasurementsGUI();
  vtkMeasurementsGUI(const vtkMeasurementsGUI&);
  void operator=(const vtkMeasurementsGUI&);

  /// 
  /// updates status text in the slicer window.
  void SetStatusText( const char *txt);
  vtkMeasurementsLogic *Logic;

  /// Description
  /// transform widget
  vtkAffineRepresentation2D *TransformRepresentation;
  vtkAffineWidget *TransformWidget;


  /// 
  /// Transform GUI elements
  vtkKWCheckButton *TransformCheckButton;
  vtkSlicerNodeSelectorWidget* TransformableNodeSelectorWidget;

  /// 
  /// ruler gui elements
  vtkMeasurementsRulerWidget *RulerWidget;

  /// 
  /// angle widget gui elements
  vtkMeasurementsAngleWidget *AngleWidget;
};

#endif

