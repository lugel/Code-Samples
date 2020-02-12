
package org.me.calculator;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlType;


/**
 * <p>Java class for add complex type.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.
 * 
 * <pre>
 * &lt;complexType name="add"&gt;
 *   &lt;complexContent&gt;
 *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType"&gt;
 *       &lt;sequence&gt;
 *         &lt;element name="rangeBegin" type="{http://www.w3.org/2001/XMLSchema}int"/&gt;
 *         &lt;element name="rangeEnd" type="{http://www.w3.org/2001/XMLSchema}int"/&gt;
 *         &lt;element name="whichOne" type="{http://www.w3.org/2001/XMLSchema}int"/&gt;
 *         &lt;element name="toCheck" type="{http://www.w3.org/2001/XMLSchema}int"/&gt;
 *       &lt;/sequence&gt;
 *     &lt;/restriction&gt;
 *   &lt;/complexContent&gt;
 * &lt;/complexType&gt;
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "add", propOrder = {
    "rangeBegin",
    "rangeEnd",
    "whichOne",
    "toCheck"
})
public class Add {

    protected int rangeBegin;
    protected int rangeEnd;
    protected int whichOne;
    protected int toCheck;

    /**
     * Gets the value of the rangeBegin property.
     * 
     */
    public int getRangeBegin() {
        return rangeBegin;
    }

    /**
     * Sets the value of the rangeBegin property.
     * 
     */
    public void setRangeBegin(int value) {
        this.rangeBegin = value;
    }

    /**
     * Gets the value of the rangeEnd property.
     * 
     */
    public int getRangeEnd() {
        return rangeEnd;
    }

    /**
     * Sets the value of the rangeEnd property.
     * 
     */
    public void setRangeEnd(int value) {
        this.rangeEnd = value;
    }

    /**
     * Gets the value of the whichOne property.
     * 
     */
    public int getWhichOne() {
        return whichOne;
    }

    /**
     * Sets the value of the whichOne property.
     * 
     */
    public void setWhichOne(int value) {
        this.whichOne = value;
    }

    /**
     * Gets the value of the toCheck property.
     * 
     */
    public int getToCheck() {
        return toCheck;
    }

    /**
     * Sets the value of the toCheck property.
     * 
     */
    public void setToCheck(int value) {
        this.toCheck = value;
    }

}
