/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package org.me.calculator.client;

import java.io.Closeable;
import java.io.IOException;
import java.io.PrintWriter;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.xml.ws.WebServiceRef;
import org.me.calculator.CalculatorWSService;

/**
 * main client class for operations
 * @author Wojciech Król
 * @version 6.0
 */
@WebServlet(name = "ClientServlet", urlPatterns = {"/ClientServlet"})
public class ClientServlet extends HttpServlet {

    @WebServiceRef(wsdlLocation = "WEB-INF/wsdl/localhost_8080/CalculatorApp/CalculatorWSService.wsdl")
    private CalculatorWSService service;

    /**
     * Processes requests for both HTTP <code>GET</code> and <code>POST</code>
     * methods.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");
        PrintWriter out = response.getWriter();
        
        int rangeBegin = 0;
        int rangeEnd = 0;
        int whichOne = 0;
        int toCheck = 0;
        
        String isIt = "";
        String found = "";
        String pNumbers = "";
        int tmp = 0;
        
        try {
            out.println("<h1>Servlet ClientServlet at " + request.getContextPath() + "</h1>");
            org.me.calculator.CalculatorWS port = service.getCalculatorWSPort();
            
            rangeBegin = Integer.parseInt(request.getParameter("rangeBegin"));
            rangeEnd = Integer.parseInt(request.getParameter("rangeEnd"));
            whichOne = Integer.parseInt(request.getParameter("whichOne"));
            toCheck = Integer.parseInt(request.getParameter("toCheck"));
            
            if (rangeBegin > rangeEnd) {
                out.println("End of the range must be bigger than the beginnig!");
            } else {
                String result = port.add(rangeBegin, rangeEnd, whichOne, toCheck);
                char firstChar = result.charAt(0);
                if(firstChar == 'f') {
                    isIt = result.substring(0,5);
                    tmp = result.indexOf("[");
                    found = result.substring(5,tmp);
                    pNumbers = result.substring(tmp);
                } else {
                    isIt = result.substring(0,4);
                    tmp = result.indexOf("[");
                    found = result.substring(4,tmp);
                    pNumbers = result.substring(tmp);
                }
                
                out.println("Primes in range: " + pNumbers);
                out.println("<br>" + whichOne + " prime number is " + found);
                out.println("<br>" + toCheck + " is a prime number: " + isIt);
                ((Closeable)port).close();
            }

        } finally {
            out.close();
        }
    }

    // <editor-fold defaultstate="collapsed" desc="HttpServlet methods. Click on the + sign on the left to edit the code.">
    /**
     * Handles the HTTP <code>GET</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    /**
     * Handles the HTTP <code>POST</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    /**
     * Returns a short description of the servlet.
     *
     * @return a String containing servlet description
     */
    @Override
    public String getServletInfo() {
        return "Short description";
    }// </editor-fold>

}
