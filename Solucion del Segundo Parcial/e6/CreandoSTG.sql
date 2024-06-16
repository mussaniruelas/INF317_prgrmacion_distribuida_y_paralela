use staging_AdventureWorksLT2022;

-- Dimension de Tiempo
CREATE TABLE DimTiempo (
    TimeKey INT IDENTITY(1,1) PRIMARY KEY,
    DateID INT,
    OrderDate DATE,
    DueDate DATE,
    ShipDate DATE,
    SellStartDate DATE,
    SellEndDate DATE,
    DiscontinuedDate DATE
);
select * from DimTiempo;

-- Dimension de Direccion
CREATE TABLE DimDireccion (
    AddressKey INT IDENTITY(1,1) PRIMARY KEY,
    AddressID INT,
    AddressLine1 NVARCHAR(60),
    AddressLine2 NVARCHAR(60),
    City NVARCHAR(30),
    StateProvince NVARCHAR(50),
    CountryRegion NVARCHAR(50)
);
select * from DimDireccion;

--Dimension de Comprador
CREATE TABLE DimComprador (
    CustomerKey INT IDENTITY(1,1) PRIMARY KEY,
    CustomerID INT,
    Title NVARCHAR(8),
    FirstName NVARCHAR(50),
    MiddleName NVARCHAR(50),
    LastName NVARCHAR(50),
    CompanyName NVARCHAR(128),
    AddressType NVARCHAR(50),
    AddressLine1 NVARCHAR(60),
    AddressLine2 NVARCHAR(60),
    City NVARCHAR(30),
    StateProvince NVARCHAR(50),
    CountryRegion NVARCHAR(50)
);
select * from DimComprador;

-- Dimension de Productor
CREATE TABLE DimProducto (
    ProductKey INT IDENTITY(1,1) PRIMARY KEY,
    ProductID INT,
    Name NVARCHAR(50),
    Color NVARCHAR(15),
    StandardCost MONEY,
    ListPrice MONEY,
    ProductCategory NVARCHAR(50),
    ParentProductCategory NVARCHAR(50),
    Size NVARCHAR(5),
    Weight DECIMAL(8, 2),
    Model NVARCHAR(50)
);
select * from DimProducto;

--Tabla de Hechos de Ventas
CREATE TABLE FactSales (
    SalesOrderKey INT IDENTITY(1,1) PRIMARY KEY,
    SalesOrderID INT,
    DateKey INT,
    ShipToAddressKey INT,
    BillToAddressKey INT,
    CustomerKey INT,
    ProductKey INT,
    SalesOrderNumber NVARCHAR(25),
    PurchaseOrderNumber NVARCHAR(25),
    AccountNumber NVARCHAR(15),
    SubTotal MONEY,
    TaxAmt MONEY,
    Freight MONEY,
    TotalDue MONEY,
    UnitPrice MONEY,
    UnitPriceDiscount MONEY,
    LineTotal MONEY,
    FOREIGN KEY (DateKey) REFERENCES DimTiempo(TimeKey),
    FOREIGN KEY (ShipToAddressKey) REFERENCES DimDireccion(AddressKey),
    FOREIGN KEY (BillToAddressKey) REFERENCES DimDireccion(AddressKey),
    FOREIGN KEY (CustomerKey) REFERENCES DimComprador(CustomerKey),
    FOREIGN KEY (ProductKey) REFERENCES DimProducto(ProductKey)
);
select * from FactSales;

/*Desactivar las claves foraneas en staging*/
ALTER TABLE FactSales NOCHECK CONSTRAINT FK__FactSales__DateK__3F466844;
ALTER TABLE FactSales NOCHECK CONSTRAINT FK__FactSales__ShipT__403A8C7D;
ALTER TABLE FactSales NOCHECK CONSTRAINT FK__FactSales__BillT__412EDB06; --este no es necesario
ALTER TABLE FactSales NOCHECK CONSTRAINT FK__FactSales__Custo__4222D4EF;
ALTER TABLE FactSales NOCHECK CONSTRAINT FK__FactSales__Produ__4316F928;

/* Eliminar los datos de las tablas */
DELETE FROM FactSales;

-- Eliminar datos de las tablas de dimensiones
DELETE FROM DimTiempo;
DELETE FROM DimDireccion;
DELETE FROM DimComprador;
DELETE FROM DimProducto;


/*Activar las claves foraneas en staging*/
ALTER TABLE FactSales WITH CHECK CHECK CONSTRAINT FK__FactSales__DateK__3F466844;
ALTER TABLE FactSales WITH CHECK CHECK CONSTRAINT FK__FactSales__ShipT__403A8C7D;
ALTER TABLE FactSales WITH CHECK CHECK CONSTRAINT FK__FactSales__BillT__412EDB06;
ALTER TABLE FactSales WITH CHECK CHECK CONSTRAINT FK__FactSales__Custo__4222D4EF;
ALTER TABLE FactSales WITH CHECK CHECK CONSTRAINT FK__FactSales__Produ__4316F928;

/* Select de las tablas */
select * from DimTiempo;
select * from DimDireccion;
select * from DimComprador;
select * from DimProducto;
select * from FactSales;


SELECT DISTINCT DateKey 
FROM FactSales 
WHERE DateKey NOT IN (SELECT TimeKey FROM DimTiempo);

INSERT INTO FactSales (
	SalesOrderID, DateKey, 
	ShipToAddressKey, 
	BillToAddressKey, 
	CustomerKey, 
	ProductKey, 
	SalesOrderNumber, 
	PurchaseOrderNumber, 
	AccountNumber, 
	SubTotal, 
	TaxAmt, 
	Freight, 
	TotalDue, 
	UnitPrice, 
	UnitPriceDiscount, 
	LineTotal)
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
from AdventureWorksLT2022.SalesLT.SalesOrderHeader oh
left join AdventureWorksLT2022.SalesLT.SalesOrderDetail od
on oh.SalesOrderID = od.SalesOrderID
inner join AdventureWorksLT2022.SalesLT.Product p
on od.ProductID = p.ProductID
order by oh.SalesOrderID;

