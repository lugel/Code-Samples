/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package tests;
import model.*;
import org.junit.*;
import java.util.*;
import static org.junit.Assert.*;

/**
 *
 * @author Wojciech Król   
 * @version 2.1 added tests for negative numbers in range
 */
public class ModelTest // class for testing purposes
{
    Model ModelTest;
     
    @Before
    public void setup()
    {
        ModelTest = new Model();
    }
    
    @Test
    public void testFindPrimesInRange() throws MyException
    {
        @SuppressWarnings("UseOfObsoleteCollectionType")
        Vector<Integer> testVec = new Vector<>();
        
        try
        {
            ModelTest.findPrimesInRange(10,20,testVec);
        }
        catch (MyException e)
        {
            fail("Proper range fails");
        }
        
        try
        {
            ModelTest.findPrimesInRange(-10,20,testVec);
        }
        catch (MyException e)
        {
            fail("Proper range fails");
        }
        
        try
        {
            ModelTest.findPrimesInRange(20,10,testVec);
            fail("Exception should be thrown because the begining is a larger number then the end");
        }
        catch (MyException e)
        {
            
        }
        
        try
        {
            ModelTest.findPrimesInRange(10,10,testVec);
            fail("Exception should be thrown because the range equals zero");
        }
        catch (MyException e)
        {
            
        }
    }
    
    @Test
    public void testIsPrime()
    {
        assertEquals("5 is a prime number", ModelTest.isPrime(5), true);
        
        assertEquals("6 is not a prime number", ModelTest.isPrime(6), false);
    }
    
    @Test
    public void testRetrunPrime()
    {
        assertEquals("Thrid prime number is 5", ModelTest.retrunPrime(3),5);
        
        assertEquals("Fourth prime number is 7", ModelTest.retrunPrime(4),7);
    }
}
