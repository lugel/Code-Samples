/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

/**
 *
 * @author Wojciech Krol
 * @version 2.0
 */
public class MyException extends Exception
{
    public MyException() {}
    
    /**
     * constructor with the message for given exception
     * @param msg message that is given when exception exists
     */
    public MyException(String msg) 
    {
        super(msg);
    }
    
}
