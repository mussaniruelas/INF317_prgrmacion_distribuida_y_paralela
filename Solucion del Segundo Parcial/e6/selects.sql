use AdventureWorksLT2022;


-- dim producto
select * from SalesLT.ProductModel;
select * from SalesLT.ProductCategory;
select * from SalesLT.Product;
select * from SalesLT.ProductModel;
select * from SalesLT.ProductModelProductDescription;
select * from SalesLT.ProductDescription;

-- dim tiempo
select * from SalesLT.Address;
select * from SalesLT.CustomerAddress;


-- dim direccion
select * from SalesLT.Address;
select * from SalesLT.CustomerAddress;
select * from SalesLT.Customer;

select * from SalesLT.Address;


-- hechos ventas
select * from SalesLT.SalesOrderDetail;
select * from SalesLT.SalesOrderHeader;