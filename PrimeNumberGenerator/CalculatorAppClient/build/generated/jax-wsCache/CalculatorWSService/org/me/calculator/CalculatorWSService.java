
package org.me.calculator;

import java.net.MalformedURLException;
import java.net.URL;
import javax.xml.namespace.QName;
import javax.xml.ws.Service;
import javax.xml.ws.WebEndpoint;
import javax.xml.ws.WebServiceClient;
import javax.xml.ws.WebServiceException;
import javax.xml.ws.WebServiceFeature;


/**
 * This class was generated by the JAX-WS RI.
 * JAX-WS RI 2.2.11-b150120.1832
 * Generated source version: 2.2
 * 
 */
@WebServiceClient(name = "CalculatorWSService", targetNamespace = "http://calculator.me.org/", wsdlLocation = "http://localhost:8080/CalculatorApp/CalculatorWSService?wsdl")
public class CalculatorWSService
    extends Service
{

    private final static URL CALCULATORWSSERVICE_WSDL_LOCATION;
    private final static WebServiceException CALCULATORWSSERVICE_EXCEPTION;
    private final static QName CALCULATORWSSERVICE_QNAME = new QName("http://calculator.me.org/", "CalculatorWSService");

    static {
        URL url = null;
        WebServiceException e = null;
        try {
            url = new URL("http://localhost:8080/CalculatorApp/CalculatorWSService?wsdl");
        } catch (MalformedURLException ex) {
            e = new WebServiceException(ex);
        }
        CALCULATORWSSERVICE_WSDL_LOCATION = url;
        CALCULATORWSSERVICE_EXCEPTION = e;
    }

    public CalculatorWSService() {
        super(__getWsdlLocation(), CALCULATORWSSERVICE_QNAME);
    }

    public CalculatorWSService(WebServiceFeature... features) {
        super(__getWsdlLocation(), CALCULATORWSSERVICE_QNAME, features);
    }

    public CalculatorWSService(URL wsdlLocation) {
        super(wsdlLocation, CALCULATORWSSERVICE_QNAME);
    }

    public CalculatorWSService(URL wsdlLocation, WebServiceFeature... features) {
        super(wsdlLocation, CALCULATORWSSERVICE_QNAME, features);
    }

    public CalculatorWSService(URL wsdlLocation, QName serviceName) {
        super(wsdlLocation, serviceName);
    }

    public CalculatorWSService(URL wsdlLocation, QName serviceName, WebServiceFeature... features) {
        super(wsdlLocation, serviceName, features);
    }

    /**
     * 
     * @return
     *     returns CalculatorWS
     */
    @WebEndpoint(name = "CalculatorWSPort")
    public CalculatorWS getCalculatorWSPort() {
        return super.getPort(new QName("http://calculator.me.org/", "CalculatorWSPort"), CalculatorWS.class);
    }

    /**
     * 
     * @param features
     *     A list of {@link javax.xml.ws.WebServiceFeature} to configure on the proxy.  Supported features not in the <code>features</code> parameter will have their default values.
     * @return
     *     returns CalculatorWS
     */
    @WebEndpoint(name = "CalculatorWSPort")
    public CalculatorWS getCalculatorWSPort(WebServiceFeature... features) {
        return super.getPort(new QName("http://calculator.me.org/", "CalculatorWSPort"), CalculatorWS.class, features);
    }

    private static URL __getWsdlLocation() {
        if (CALCULATORWSSERVICE_EXCEPTION!= null) {
            throw CALCULATORWSSERVICE_EXCEPTION;
        }
        return CALCULATORWSSERVICE_WSDL_LOCATION;
    }

}
