#include "gearimpl/FixedPadSizeDiskLayout.h"

#include <cmath>
#include <math.h>
#include <iostream>
#include <stdexcept>

namespace gear {
  
  FixedPadSizeDiskLayout::FixedPadSizeDiskLayout( double rMin, double rMax, 
						  double padHeight, double padWidth, 
						  int nRow , 
						  double padGap ) : 
    _rMin( rMin ),
    _rMax( rMax ),
    _padWidth( padWidth ) ,
    _padHeight(padHeight)  ,
    _padGap( padGap ) 
  {
    
    _extent.resize(4) ;
    _extent[0] = _rMin ;
    _extent[1] = _rMax ;
    _extent[2] = 0.0 ;
    _extent[3] = 2. * M_PI ;

    // compute the row properties

    int nr = (int) std::floor ( ( rMax - rMin ) /  _padHeight ) ;

    _nRow = ( nRow > 0 ) ? nRow : nr ;

    if( nRow > nr ) {

      std::cout << " WARNING: FixedPadSizeDiskLayout() :  cannot place  " <<  nRow 
		<< " rows of height " <<  _padHeight
		<< " mm between rMin = " << rMin << " mm and rMax = " << rMax 
		<< " mm -  will use nRow = " << nr << " !! " 
		<< std::endl ;
	
      _nRow = nr ;

    } 

    _padIndices.resize( _nRow ) ;

    _rowHeight =  ( rMax - rMin ) / _nRow ;

    _nPad  = 0 ;

    for( int i = 0 ; i < _nRow ; i++ ) {

      Row row ;
      
      row.RCenter  =  rMin + ( i * _rowHeight )  + .5 * _rowHeight ;

      double u = 2. * row.RCenter * M_PI  ;

      row.NPad = (int) std::floor( u / (_padWidth + padGap )  ) ; 

      row.PhiPad = 2. * M_PI  / row.NPad ;

//       std::cout << "  row, row.NPad , row.PhiPad : " << i << " , " << row.NPad << " , " <<  row.PhiPad 
// 		<< std::endl; 

      _nPad += row.NPad ;

      _rows.push_back( row ) ;
    }
    
  }
  
  int FixedPadSizeDiskLayout::getNRows() const {
    return _rows.size() ;
  }


  double FixedPadSizeDiskLayout::getPadWidth(int padIndex) const {

    // phi of pad in row :
    int rowNum =  getRowNumber( padIndex ) ;
    try {  

      // need to return padWidth in radians !!
      return _padWidth / _rows.at( rowNum ).RCenter ; 

    } 
    catch(std::out_of_range){
      return 0. ;
    }
  } 



  Point2D FixedPadSizeDiskLayout::getPadCenter(int padIndex)  const {
    
    int rowNum =  getRowNumber( padIndex ) ;
    int padNum =  getPadNumber( padIndex ) ;

    double r = _rows[ rowNum ].RCenter ; 

    double phi =  ( padNum + 0.5 ) * _rows[ rowNum ].PhiPad ; 
    
    return std::make_pair( r , phi ) ;
  }

  const std::vector<int>& FixedPadSizeDiskLayout::getPadsInRow(int rowNumber) const {

    static std::vector<int> empty ;
    try {
      if( _padIndices.at(rowNumber )  == 0 ) {
	
	int nPad = _rows.at(rowNumber).NPad ;
	
	_padIndices[ rowNumber ]  = new std::vector<int>( nPad )  ;
	
	for(int i = 0 ; i < nPad ; i++){
	  
	  _padIndices[rowNumber]->operator[](i)  = getPadIndex( rowNumber , i  ) ;
	}
	
      }
    } catch( std::out_of_range& r) {
      
      //       std::cout << " FixedPadSizeDiskLayout::getPadsInRow : no row " << rowNumber << std::endl ;
      return empty ;

    }

    return *_padIndices[ rowNumber ] ;

  }

  int FixedPadSizeDiskLayout::getPadIndex(int rowNum, int padNum) const {

    return  (rowNum << 16 ) | ( 0x0000ffff & padNum ) ;

  }

  int FixedPadSizeDiskLayout::getNearestPad(double r, double phi) const {

    if( r < 0.0 ) r = 0.0 ;

    while( phi < 0.0 ) {  phi += 2. * M_PI  ; }
    while( phi > 2*M_PI ) {  phi -= 2. * M_PI  ; }

    int rowNum = r < _rMin ? 0 : (int) std::floor( ( r - _rMin ) / _rowHeight  ) ;

    if( rowNum >= _nRow  )       
      rowNum = _nRow -1 ;
      

    int padNum = (int) std::floor( phi / _rows[ rowNum ].PhiPad ) ;
    
    if( padNum >=  _rows[ rowNum ].NPad  )
      padNum = _rows[ rowNum ].NPad  - 1 ;
 
    //     std::cout << " FixedPadSizeDiskLayout::getNearestPad( " << r << " , " << phi << " ) " 
    // 	      << "  _rows[ rowNum ].PhiPad : " <<  _rows[ rowNum ].PhiPad 
    // 	      << std::endl ;

    return getPadIndex( rowNum , padNum ) ;
				  
  }

  int FixedPadSizeDiskLayout::getRightNeighbour(int padIndex) const {
    
    return( getPadIndex(  getRowNumber( padIndex) , getPadNumber( padIndex ) - 1  ) ) ;
    
  }

  int FixedPadSizeDiskLayout::getLeftNeighbour(int padIndex) const {
      
    return( getPadIndex(  getRowNumber( padIndex) , getPadNumber( padIndex ) + 1  ) ) ;
  }
  

  bool FixedPadSizeDiskLayout::isInsidePad(double r, double phi, int padIndex) const {
      
//     double rCenter =  0. ;
//     int rowNumber = getRowNumber( padIndex ) ;
//     try {  rCenter = _rows.at( rowNumber ).RCenter ; 
//     } 
//     catch(std::out_of_range){
//       return false ;
//     }
      
    if( r < _rMin || r > _rMax )
      return false ;
    
    Point2D p  = getPadCenter( padIndex ) ;
    
//     double phiPadHalf = 0.5 * _padWidth / rCenter ;
    
    double phiPadHalf = 0.5 * getPadWidth( padIndex ) ;
    
    
//     std::cout << " isInsidePad( " << rowNumber << ", " <<  phiPadHalf  << ", " << 0.5 *  _padHeight  
// 	      << " - ( " << p.first << ", " << p.second << " ) " 
// 	      << (std::abs( r - p.first ) <= 0.5 * _padHeight) << "&&"
// 	      << (std::abs( phi - p.second ) <= phiPadHalf)
// 	      << std::endl ;

    return  ( std::abs( r - p.first ) <= 0.5 * _padHeight  && 
	      std::abs( phi - p.second ) <= phiPadHalf  ) ;
    
  }

  bool FixedPadSizeDiskLayout::isInsidePad(double r, double phi) const {

    if( r < _rMin || r > _rMax )
      return false ;

    return  isInsidePad( r , phi , getNearestPad( r, phi ) )  ;

  }
  
} // namespace

