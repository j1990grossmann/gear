#ifndef GEAR_XMLHandler_H
#define GEAR_XMLHandler_H 1

#include <string>

namespace gear {

  class TiXmlElement ;
  class GearParameters ;
  class GearMgr ;
  
  /** Interface for XML handlers of GEAR classes.
   * 
   * @author F. Gaede, DESY
   * @version $Id: XMLHandler.h,v 1.2 2005-11-25 16:08:15 gaede Exp $
   */
  class XMLHandler {
    
  public: 
    
    
    /** Creates an XML node for the given parameters 
     */
    virtual TiXmlElement toXML( const GearParameters & parameters ) const = 0 ;
    
    
    /** Creates the approprtiate GearParameters subclass from the given
     *  XML element (node) and adss it to the given instance of GearMgr (if != 0 ).
     */
    virtual GearParameters* fromXML( const TiXmlElement* xmlElement , GearMgr* gearMgr=0) const = 0 ;
    
    
  }; // class
  

  class TiXmlNode ;

  /** Helper method used for parsing XML */
  std::string getXMLAttribute(const  TiXmlNode* node , const std::string& name ) ;    

  /** Helper method used for parsing XML - returns the attribute 'value' of the named child element as double 
   */
  std::string getChildElementValue(const TiXmlNode* node , const std::string& name ) ;


} // namespace gear

#endif /* ifndef GEAR_XMLHandler_H */