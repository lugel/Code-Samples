
package org.me.calculator;

import javax.xml.bind.JAXBElement;
import javax.xml.bind.annotation.XmlElementDecl;
import javax.xml.bind.annotation.XmlRegistry;
import javax.xml.namespace.QName;


/**
 * This object contains factory methods for each 
 * Java content interface and Java element interface 
 * generated in the org.me.calculator package. 
 * <p>An ObjectFactory allows you to programatically 
 * construct new instances of the Java representation 
 * for XML content. The Java representation of XML 
 * content can consist of schema derived interfaces 
 * and classes representing the binding of schema 
 * type definitions, element declarations and model 
 * groups.  Factory methods for each of these are 
 * provided in this class.
 * 
 */
@XmlRegistry
public class ObjectFactory {

    private final static QName _Add_QNAME = new QName("http://calculator.me.org/", "add");
    private final static QName _AddResponse_QNAME = new QName("http://calculator.me.org/", "addResponse");
    private final static QName _History_QNAME = new QName("http://calculator.me.org/", "history");
    private final static QName _HistoryResponse_QNAME = new QName("http://calculator.me.org/", "historyResponse");
    private final static QName _Persist_QNAME = new QName("http://calculator.me.org/", "persist");
    private final static QName _PersistResponse_QNAME = new QName("http://calculator.me.org/", "persistResponse");

    /**
     * Create a new ObjectFactory that can be used to create new instances of schema derived classes for package: org.me.calculator
     * 
     */
    public ObjectFactory() {
    }

    /**
     * Create an instance of {@link Add }
     * 
     */
    public Add createAdd() {
        return new Add();
    }

    /**
     * Create an instance of {@link AddResponse }
     * 
     */
    public AddResponse createAddResponse() {
        return new AddResponse();
    }

    /**
     * Create an instance of {@link History }
     * 
     */
    public History createHistory() {
        return new History();
    }

    /**
     * Create an instance of {@link HistoryResponse }
     * 
     */
    public HistoryResponse createHistoryResponse() {
        return new HistoryResponse();
    }

    /**
     * Create an instance of {@link Persist }
     * 
     */
    public Persist createPersist() {
        return new Persist();
    }

    /**
     * Create an instance of {@link PersistResponse }
     * 
     */
    public PersistResponse createPersistResponse() {
        return new PersistResponse();
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link Add }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://calculator.me.org/", name = "add")
    public JAXBElement<Add> createAdd(Add value) {
        return new JAXBElement<Add>(_Add_QNAME, Add.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link AddResponse }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://calculator.me.org/", name = "addResponse")
    public JAXBElement<AddResponse> createAddResponse(AddResponse value) {
        return new JAXBElement<AddResponse>(_AddResponse_QNAME, AddResponse.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link History }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://calculator.me.org/", name = "history")
    public JAXBElement<History> createHistory(History value) {
        return new JAXBElement<History>(_History_QNAME, History.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link HistoryResponse }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://calculator.me.org/", name = "historyResponse")
    public JAXBElement<HistoryResponse> createHistoryResponse(HistoryResponse value) {
        return new JAXBElement<HistoryResponse>(_HistoryResponse_QNAME, HistoryResponse.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link Persist }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://calculator.me.org/", name = "persist")
    public JAXBElement<Persist> createPersist(Persist value) {
        return new JAXBElement<Persist>(_Persist_QNAME, Persist.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link PersistResponse }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://calculator.me.org/", name = "persistResponse")
    public JAXBElement<PersistResponse> createPersistResponse(PersistResponse value) {
        return new JAXBElement<PersistResponse>(_PersistResponse_QNAME, PersistResponse.class, null, value);
    }

}
