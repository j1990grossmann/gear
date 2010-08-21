// -*- C++ -*-
#ifndef GEAR_LAYERLAYOUT_H
#define GEAR_LAYERLAYOUT_H 1

// -*- Java -*-

namespace gear {

/** Abstract description of a layered layout detector - typically a 
 *  a sampling calorimeter.
 * 
 * @author F. Gaede, DESY
 * @version $Id: LayerLayout.aid,v 1.1.1.1 2005-09-13 14:41:03 gaede Exp $
 */
class LayerLayout {

public: 
    /// Destructor.
    virtual ~LayerLayout() { /* nop */; }

    /** The total number of layers.
     */
    virtual int getNLayers() const = 0;

    /** The distance of the layer layerIndex from the origin - layer indexing starts at 0
     *  for the layer closest to the origin.
     */ 
    virtual double getDistance(int layerIndex) const = 0;

    /** The thickness of the layer layerIndex - layer indexing starts at 0
     *  for the layer closest to the origin.
     */ 
    virtual double getThickness(int layerIndex) const = 0;

    /** The thickness of the absorber part of the layer layerIndex - layer indexing starts at 0
     *  for the layer closest to the origin.
     */ 
    virtual double getAbsorberThickness(int layerIndex) const = 0;

    /** The cell size along the first axis where first is either along the beam (barrel type) or up (endcap)
     * or the direction closest to that.   
     */ 
    virtual double getCellSize0(int layerIndex) const = 0;

    /** The second cell size, perpendicular to the first direction (getCellSize0()) and the depth of the layers.
     */ 
    virtual double getCellSize1(int layerIndex) const = 0;
}; // class
} // namespace gear
#endif /* ifndef GEAR_LAYERLAYOUT_H */