/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package org.me.calculator;

import java.io.Serializable;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;

/**
 * Class Data for database management
 * @author Wojciech Król
 * @version 6.0
 */
@Entity
public class Data implements Serializable {

    /**
     * ID generation
     */
    private static final long serialVersionUID = 1L;
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    

    private Long id;

    
    public Long getId() {
        return id;
    }

    
    public void setId(Long id) {
        this.id = id;
    }
    

    private boolean isPrime;

    
    public boolean getIsPrime() {
        return isPrime;
    }
    
    
    public void setIsPrime(boolean isIt) {
        this.isPrime = isIt;
    }
    

    private int whichOne;
    
    
    public int getWhichOne() {
        return whichOne;
    }
    
    
    public void setWhichOne(int found) {
        this.whichOne = found;
    }
    
    private String inRange;
    
    
    public String getInRange() {
        return inRange;
    }
    
    
    public void setInRange(String pNumbers) {
        this.inRange = pNumbers;
    }

    /**
     * Hashcode function
     */
    @Override
    public int hashCode() {
        int hash = 0;
        hash += (id != null ? id.hashCode() : 0);
        return hash;
    }
    /**
     * Hashcode function
     * @param object
     */
    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Data)) {
            return false;
        }
        Data other = (Data) object;
        if ((this.id == null && other.id != null) || (this.id != null && !this.id.equals(other.id))) {
            return false;
        }
        return true;
    }
     /**
     * toString function 
     */
    @Override
    public String toString() {
        String out = String.format("<br>Primes in range: %s <br>Desired prime number: %d <br>Was it a prime number: %b", inRange, whichOne, isPrime);
        return out;
    }
    
}
