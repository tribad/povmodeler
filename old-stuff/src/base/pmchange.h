// **************************************************************************
//
// Modul-Name        : pmchange.h
// Author            : Hans-Juergen Lange <hjl@simulated-universe.de>
// Creation-Date     : 23.10.2019
//
//  Copyrights by Hans-Juergen Lange. All rights reserved.
//
// **************************************************************************

#ifndef PMCHANGE_H
#define PMCHANGE_H

/**
 * Constants for object changes
 *
 * PMCAdd: An object was added
 *
 * PMCRemove: An object was removed. A signal with this constant has
 * to be emitted _before_ the object is removed.
 *
 * PMCChildren: Some children are added or removed. Do not use. Use PMCAdd and
 * PMCRemove for all childrens.
 *
 * PMCData: Data (for dialog views) is changed
 *
 * PMCDescription: The name or pixmap of the object has changed. Always
 * together with PMCData.
 *
 * PMCViewStructure: The rendering has changed
 *
 * PMCNewSelection: The object was selected and all other deleselected.
 * If the changed object is 0, all objects are deselected!
 *
 * PMCSelected: The object was selected.
 *
 * PMCDeselected: The object was deselected.
 *
 * PMCNewControlPoints: The list of control points has changed.
 *
 * PMCControlPointSelection: The control point selection has changed.
 *
 * PMCInsertError: The added object couldn't be inserted and was appended
 * to the insert errors. Always together with PMCAdd.
 *
 * PMCNothing: Nothing was changed
 */
enum PMChange
{
   PMCNothing = 0, PMCAdd = 1, PMCRemove = 2, PMCChildren = 4,
   PMCData = 8, PMCDescription = 16, PMCViewStructure = 32,
   PMCGraphicalChange = 64,
   PMCNewSelection = 128, PMCSelected = 256,
   PMCDeselected = 512,
   PMCNewControlPoints = 1024, PMCControlPointSelection = 2048,
   PMCInsertError = 4096
};

#endif // PMCHANGE_H
