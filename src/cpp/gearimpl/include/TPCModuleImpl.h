#ifndef TPCModuleImpl_h
#define TPCModuleImpl_h 1

#include "gear/TPCModule.h"
#include "gearimpl/GearParametersImpl.h"

namespace gear {

/** A wrapper Class for PadRowLayout2D, allowing which converts 
 * between local and global coordinate systems, and adds module 
 * appropriate functionality.
 *
 * @author M. Killenberg, (Bonn)  S. Turnbull, (Saclay/Carleton)
 * @version $Id: TPCModuleImpl.h,v 1.1 2008-12-17 09:39:46 engels Exp $
 */

class TPCModuleImpl : public GearParametersImpl, public TPCModule 
{
 protected:
    std::vector<double> _planeExtent;
    std::vector<double> _moduleExtent;
    std::vector<double> _localModuleExtent; ///< The module extend in the pad plane's coordinate system
    PadRowLayout2D * _padRowLayout;
    double _readoutFrequency;
    gear::Vector2D _offset; ///< The offset in cordinates described by _momsCoordinateType
    gear::Vector2D _offset_cartesian; ///< The offset in cartesian cordinates
    double _angle;
    int _momsCoordinateType; ///< AKA coordinate type of the TPC which contains this module
    int _moduleID;
    double _border; ///< Area around a pad Plane to extend the amplification reagion so that the outmost pads don't loose elecetrons  
    
    /** Transforms the local planeExtend to a global planeExtend, global moduleExtend 
     *  and localModuleExtend.
     */
    void convertLocalPlaneToGlobalPlaneExtend(void); 

    /** Calculate the global extent for a given local extent if both local and global 
     *  coordinate system are cartesian.
     */
    std::vector<double> calculateGlobalExtentCartesianCartesian( std::vector<double> localExtent );

    /** Calculate the global extent for a given local extent if both local and global 
     *  coordinate system are polar.
     */
    std::vector<double> calculateGlobalExtentPolarPolar( std::vector<double> localExtent );
 
   /** Calculate the global extent for a given local extent if the global coordinates are
    *  cartesian and the module is polar.
    */
    std::vector<double> calculateGlobalExtentCartesianPolar( std::vector<double> localExtent );

  /** function to copy all internal variables, incl. the objects
   *  pointed to and owned by the TPCModule.
   *  Used by constructor and assigment operator to avoid code duplication
   */
  void copy_and_assign(const  TPCModuleImpl & );

  /** function to delete all the objects
   *  pointed to and owned by the TPCModule.
   *  Used by desctructor and assigment operator to avoid code duplication
   */
  void cleanup();
    

 public: 
    
    /** Construct the empty RectangularPadRowLayout with the width and x position
     *  specified through  xMin and xMax and an optional yMin - yMax will be computed from 
     *  the rows that are added with addRow().
     */
    TPCModuleImpl(int moduleID, PadRowLayout2D *padRowLayout,int TPCCoordinateType,  double readoutFrequency = 0) ;

    /// The copy constructor
    TPCModuleImpl(const TPCModuleImpl &);

    /// The assignment operator
    TPCModuleImpl & operator = (const TPCModuleImpl &);
    
    /// Destructor.
    virtual ~TPCModuleImpl() ; 
    
    /* The clone function. Used to access the copy-constructor if this class via the
     * acstract PadRowLayout2D interface.
     */
    PadRowLayout2D* clone() const;

    /** 
     *	\deprecated{
     *  As there now is more than one implementation for each coordinate type
     *  this is not sufficient to distinguish the implementations any more.
     *  Use getPadLayoutImplType() to get the implementation type.
     *  Use getCoordinateType() to get the type of the coordinate system.
     *  
     *  For backward compatibility this function returns
     *  getCoordinateType().}
     */
    virtual int getPadLayoutType() const;

    /** The type of the row layout implementation:
     *  PadRowLayout2D.TPCMODULE
     */
    virtual int getPadLayoutImplType() const;

    /** The type of the contained pad layouts coordinate system.
      */
    virtual int getCoordinateType()    const;

    
    /** The shape of the pads: PadRowLayout2D::RECTANGLE (i.e. keystone).
     */ 
    virtual int getPadShape() const { return _padRowLayout->getPadShape(); }
    
    /** The total number of pads in the TPC.
     */
    virtual int getNPads() const { return _padRowLayout->getNPads(); }
    
    /** The number of rows.
     */
    virtual int getNRows() const { return _padRowLayout->getNRows(); }
    
    /** The row height in mm.
     */
    virtual double getRowHeight(int rowNumber) const { return _padRowLayout->getRowHeight(rowNumber); }

    /** The height of the pad in mm.
     */
    virtual double getPadWidth(int padIndex) const { return _padRowLayout->getPadWidth(padIndex); } 

    /** The center of the pad in mother's 2d coordinates, (x,y) or (r,phi). / AKA the TPC's coordinates.
     */
    virtual gear::Vector2D getPadCenter(int padIndex)  const;

    /** The height of the pad in mm.
     */
    virtual double getPadHeight(int padIndex) const { return _padRowLayout->getPadHeight(padIndex); }

    /** Indices of all pads in row rowNumber (row indices start from 0 at the
     * bottom (CARTESIAN) or at the center (POLAR)). 
     */
    virtual const std::vector<int>& getPadsInRow(int rowNumber) const { return _padRowLayout->getPadsInRow(rowNumber); } 

    /** Inherited from PadRowLayout2D, but generally not a useful measure
     *  in global coordinates, use getModuleExtent() instead.
     *  It is kept for backward compatibility, but only works if there is
     *  only one module in the end cap. The module must not have an angle
     *  or an offset, so its coordinate system is identical to the global
     *  one. 
     *  In case there is more than one module or there is an offset or angle
     *  it will throw a gear::Exception.
     */
    virtual const std::vector<double>& getPlaneExtent()  const throw (gear::Exception, std::exception);

    /** Extent of the sensitive plane in TPC's coordinate system, with extended region
     *  just outside module from _enlargeBy,  - [xmin,xmax,ymin,ymax] CARTESIAN or 
     *	[rmin,rmax,phimin,phimax] POLAR, also may contain additional deadspace due to 
     *mismatch of offset's and coordinate types.
     */
    virtual const std::vector<double>& getModuleExtent()  const {return _moduleExtent; }
    
    /** The module extent in local coordinates. This is the (local) pad plane,
     * enlarged by the border. As the plane extent in global coordinates does
     * not correspond to the actual shape, this is the only way to describe
     * the module extent without dead space (everything in the module extent
     * is considerred active, for instance due to a resistive coating which
     * causes signals even if there is no pad at the specific position).
     * \attention Returns LOCAL coordinates!   
     */   
    virtual const std::vector<double>& getLocalModuleExtent()  const {return _localModuleExtent; }

    /** The number of the row, for the given module(all modules restart 
     *at 0), that contains the pad at padIndex - numbering starts at 
     *r/y==0.
     */
    virtual int getRowNumber(int padIndex)  const { return _padRowLayout->getRowNumber(padIndex) ; } 

    /** The pad number (column) within the row  - numbering starts at x==0 (left).
     */
    virtual int getPadNumber(int padIndex) const { return _padRowLayout->getPadNumber(padIndex)  ; }

    /** Create a padIndex for the given row and pad ( column ) number 
     */
    virtual int getPadIndex(int rowNum, int padNum)  const { return _padRowLayout->getPadIndex(rowNum, padNum)  ; }

    /** The index of the pad nearest to the given point in Global 2d coordinates
     * (x,y,) or (r,phi).
     */
    virtual int getNearestPad(double x, double y)  const;

    /** The index of the right neighbour pad.
     */
    virtual int getRightNeighbour(int padIndex)  const{ return _padRowLayout->getRightNeighbour(padIndex)  ; }

    /** The index of the left neighbour pad.
     */
    virtual int getLeftNeighbour(int padIndex)  const{ return _padRowLayout->getLeftNeighbour(padIndex)  ; }

    /** True if coordinate (x,y) is within the given pad.
     */
    virtual bool isInsidePad(double c0, double c1, int padIndex)  const;

    /** True if coordinate (x,y) is within any pad.
     */
    virtual bool isInsidePad(double c0, double c1)  const;

    /** True if global coordinate (c0,c1) is within this modules
     * area of amplification/interest
     */
    virtual bool isInsideModule(double c0, double c1) const;

    /** The readout frequency in Hz.
     */
    virtual double getReadoutFrequency() const {return _readoutFrequency; }

    /** Returns the offest of Modules origin from the global origin
     *  A vector from Global (0,0) to module (0,0)
     */
    virtual const gear::Vector2D & getOffset() const { return _offset; }

    /** Returns the rotation of the module, in Rads, with respect 
     *  to the modules internal origin.
     */
    virtual double getAngle() const { return _angle; }

    /** Returns the distance from a global coodinate (c0,c1), to a given
     *  pad's nearest boundery;   (c0,c1,index) 
     */
    virtual double getDistanceToPad(double c0, double c1, int index) const;

    /** Returns distastance from a global coodinate (c0,c1), to the 
     *  module's nearest boundery;   (c0,c1) 
     */
    virtual double getDistanceToModule(double c0, double c1) const;

     /** Returns module ID
     */
    virtual int getModuleID() const { return _moduleID; }

    /**  Returns True if this and The given module * overlap pad regions
     *   Note: overlaping sensitive regions is ok, Just no two pads with
     * 	 shared physicsal space.
     */
    virtual bool isOverlapping(TPCModule * testThisModule) const;

    virtual double getBorderWidth() const { return _border;}

    /** Returns the TPCs coordinate type. Note that this is NOT the 
     *  coordinate type of the (local) pad plane on the module but 
     *  of the end plate this module is mounted in.
     */
    int getTPCCoordinateType() const {return _momsCoordinateType;}

    void setOffset(double x_r, double y_phi);
    
    void setAngle(double angle);

    void setBorderWidth(double border) ; 

    /// kept for backward compatibility, please set readout frequency in constructor
    void setReadoutFrequency(double frequency);

    /** Returns a reference to the instance of the underlaying pad layout.
     */   
    const PadRowLayout2D & getLocalPadLayout() const {return *_padRowLayout;}
    

    gear::Vector2D globalToLocal(double c0,double c1) const; ///< Transforms a point from the global coordinates to Layout2D coordinates.
    gear::Vector2D localToGlobal(double c0,double c1) const; ///< Transforms a point from the Layout2D coordinates to global coordinates. 
    
  }; // class

} // namespace gear
#endif // ifndef TPCModuleImpl_h