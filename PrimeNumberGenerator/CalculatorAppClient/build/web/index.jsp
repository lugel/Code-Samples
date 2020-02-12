<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Prime Number Generator</title>
    </head>
     <body>
        <h1>Prime Number Generator</h1>
        <form name="Submit" action="ClientServlet">&nbsp;
            <p>Beginning of the range:<input type=number size=20 name=rangeBegin></p>
            <p>End of the range:<input type=number size=20 name=rangeEnd></p>
            <p>Which prime number:<input type=number size=20 name=whichOne></p>
            <p>Number to check if it is prime:<input type=number size=20 name=toCheck></p>
            <input type="submit" value="Get Result" name="GetResult" />
        </form>
        <form name="Submit" action="ClientServletHistory">&nbsp;
            <input type="submit" value="Get History" name="GetHistory" />
        </form>
    </body>
</html>
