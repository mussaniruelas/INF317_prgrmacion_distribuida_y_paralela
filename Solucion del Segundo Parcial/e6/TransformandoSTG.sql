use AdventureWorksLT2022;

-- Dimension de Tiempo 
SELECT 
    Distinct oh.SalesOrderID as DateID,
    oh.OrderDate,
    oh.DueDate,
    oh.ShipDate,
    p.SellStartDate,
    p.SellEndDate,
    p.DiscontinuedDate
from SalesLT.SalesOrderHeader oh
left join SalesLT.SalesOrderDetail od
on oh.SalesOrderID = od.SalesOrderID
inner join SalesLT.Product p
on od.ProductID = p.ProductID
order by oh.SalesOrderID;


-- Dimension de Direccion
SELECT
    a.AddressID,
    a.AddressLine1,
    a.AddressLine2,
    a.City,
    a.StateProvince,
    a.CountryRegion
FROM SalesLT.Address a
order by a.AddressID;


--Dimension de Comprador
SELECT
    c.CustomerID,
    c.Title,
    c.FirstName,
    c.MiddleName,
    c.LastName,
    c.CompanyName,
    d.AddressType,
    d.AddressLine1,
    d.AddressLine2,
    d.City,
    d.StateProvince,
    d.CountryRegion
FROM SalesLT.Customer c
LEFT JOIN (
    SELECT 
        ca.CustomerID,
        ca.AddressType,
        a.AddressLine1,
        a.AddressLine2,
        a.City,
        a.StateProvince,
        a.CountryRegion
    FROM SalesLT.CustomerAddress ca
    INNER JOIN SalesLT.Address a ON ca.AddressID = a.AddressID
) as d ON c.CustomerID = d.CustomerID
order by c.CustomerID;


-- Dimension de Productor
SELECT  
    p.ProductID, 
    p.Name,
    p.Color,
    p.StandardCost,
    p.ListPrice,
    pc.ProductCategory,
    pc.ParentProductCategory,
    p.Size,
    p.Weight,
    m.Name as model
FROM SalesLT.Product as p
LEFT JOIN (
    SELECT 
        p1.ProductCategoryID,
        p1.Name as ProductCategory,
        p2.Name as ParentProductCategory
    FROM SalesLT.ProductCategory p1
    LEFT JOIN SalesLT.ProductCategory p2 ON p1.ParentProductCategoryID = p2.ProductCategoryID
    ORDER BY p1.ProductCategoryID
    OFFSET 4 ROWS
) as pc ON p.ProductCategoryID = pc.ProductCategoryID
LEFT JOIN SalesLT.ProductModel m ON p.ProductModelID = m.ProductModelID
order by p.ProductID;


--Tabla de Hechos de Ventas
select 
	oh.SalesOrderID,
	oh.SalesOrderID DateID,
	oh.ShipToAddressID,
	oh.BillToAddressID,
	oh.CustomerID,
	p.ProductID,
	oh.SalesOrderNumber,
	oh.PurchaseOrderNumber,
	oh.AccountNumber,
	oh.SubTotal,
	oh.TaxAmt,
	oh.Freight,
	oh.TotalDue,
	od.UnitPrice,
	od.UnitPriceDiscount,
	od.LineTotal
from SalesLT.SalesOrderHeader oh
left join SalesLT.SalesOrderDetail od
on oh.SalesOrderID = od.SalesOrderID
inner join SalesLT.Product p
on od.ProductID = p.ProductID
order by oh.SalesOrderID;

