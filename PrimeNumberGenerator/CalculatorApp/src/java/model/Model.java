/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package model;
import model.LambdaExpression.MathOperations;
import java.util.*;

/**
 *
 * @author Wojciech Krol
 * @version 2.0 added use of annotations in findPrimesInRange() method
 */
public class Model // class for processing data
{
    public Model() {}
    
    LambdaExpression lExpr = new LambdaExpression();
    
    /**
     * finds prime numbers in provided range
     * @param rangeBegin the beginning of the range
     * @param rangeEnd the end of the range
     * @param primeNumbers vector that will be filled with prime numbers
     * @throws MyException exception that gets thrown when the beginning is a bigger number than the end of the range
     */
    @SuppressWarnings("UseOfObsoleteCollectionType")
    public void findPrimesInRange(int rangeBegin, int rangeEnd, Vector<Integer> primeNumbers) throws MyException 
    {
        if (rangeBegin>=rangeEnd)
        {
            throw new MyException("Wrong range!!!");
        }
        else
        {
            boolean isPrm;
            for(int i=rangeBegin;i<=rangeEnd;i++)
            {
                isPrm = isPrime(i);
                if (isPrm)
                {
                    primeNumbers.add(i);
                }
            }
        }
    }
    
    /**
     * checks if the number is prime
     * @param number number to check if it is prime
     * @return returns either true or false
     */
    public boolean isPrime(int number) 
    {
        if (number < 2)
        {
            return false;
        }
        
        MathOperations mod = (a, b) -> a % b;
        for(int i=2;i<=java.lang.Math.sqrt(number);i++)
        {          
            if (lExpr.chosenOperation(number, i, mod) == 0)
            {
                return false;
            }
        }
        return true;
    }
    
    /**
     * finds the n. prime number
     * @param which which prime number user wanted
     * @return returns the n. prime number
     */
    public int retrunPrime(int which)
    {
        int counter=0;
        int soughtNumber=0;
        while(counter<which)
        {
            soughtNumber++;
            if (isPrime(soughtNumber))
            {
                counter++;
            }
        }
        return soughtNumber;
    }
}
