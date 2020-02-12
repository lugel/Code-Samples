/*
 * Copyright (c) 2010, Oracle. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of Oracle nor the names of its contributors
 *   may be used to endorse or promote products derived from this software without
 *   specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

package org.me.calculator;

import java.util.List;
import java.util.Vector;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.annotation.Resource;
import javax.jws.WebMethod;
import javax.jws.WebParam;
import javax.jws.WebService;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import javax.persistence.Query;
import model.Model;
import model.MyException;

    /**
     * Class connecting with database  
     * @author Wojciech Krol
     * @version 6.0
     */
@WebService()
public class CalculatorWS {
    /**
     * Persistence Context 
     */
    @PersistenceContext(unitName = "CalculatorAppPU")
    private EntityManager em;
    @Resource
    private javax.transaction.UserTransaction utx;
    
    /**
     * Model class for calculations
     */
    Model model = new Model();
    
    
    /**
     * vector for generated prime numbers' storage
     */
    private final Vector<Integer> primeNumbers = new Vector<>();
    
    
    /**
     * Web service operation
     * @param rangeBegin beginning of the given range
     * @param rangeEnd end of given range
     * @param whichOne which prime number to find
     * @param toCheck a number to check if it is a prime
     * @return all data generated
     */
    @WebMethod(operationName = "add")
    public String execute(@WebParam(name = "rangeBegin") int rangeBegin, @WebParam(name = "rangeEnd") int rangeEnd, @WebParam(name = "whichOne") int whichOne, @WebParam(name = "toCheck") int toCheck) {
        //TODO write your implementation code here:
        boolean okRange = true;
        int found = 0;
        boolean isItB = true;
        Data data = new Data();
        String output = "";
        primeNumbers.clear();
        
        try {
            model.findPrimesInRange(rangeBegin, rangeEnd, primeNumbers);
        } catch (MyException me) {
            okRange = false;
        }
        
        found = model.retrunPrime(whichOne);
        
        if(model.isPrime(toCheck)) {
            isItB = true;
        } else {  
            isItB = false;
        }
        
        output = String.format(Boolean.toString(isItB) + Integer.toString(found) + primeNumbers.toString());
        
        data.setId(0L);
        data.setIsPrime(isItB);
        data.setWhichOne(found);
        data.setInRange(primeNumbers.toString());
        this.persist(data);
        
        
        return output;
    }

    /**
     * Web service operation to select data from database
     * @return data from database
     *
    */
    @WebMethod(operationName = "history")
    public String History() {
        String out ="";
        List<Data> historyOfOperatoin=GetDataFromDataBase();
        for(Data data : historyOfOperatoin)
        {
           out += data.toString();
           out += "<br>";
        }
        return out;
    }
    
    
    /**
     * persistence method
     * @param object 
     */
    public void persist(Object object) {
        try {
            utx.begin();
            em.persist(object);
            utx.commit();
        } catch (Exception e) {
            Logger.getLogger(getClass().getName()).log(Level.SEVERE, "exception caught", e);
            throw new RuntimeException(e);
        }
    }

    /**
     * makes query
     * @return query
     */
    private List<Data> GetDataFromDataBase() {
       Query query = em.createQuery("SELECT d from Data d");
       return query.getResultList();
    }

}
