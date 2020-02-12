/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package model;


/**
 *
 * @author Wojciech Krol
 * @version 1.2
 */
public class LambdaExpression 
{
    interface MathOperations 
    {
        int operation(int a, int b);
    }

    int chosenOperation(int a, int b, MathOperations mo) 
    {
        return mo.operation(a, b);
    }
}
