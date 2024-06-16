use staging_AdventureWorksLT2022;

SELECT 
    f.name AS ForeignKeyName,
    t.name AS TableName,
    c.name AS ColumnName,
    rt.name AS ReferencedTableName,
    rc.name AS ReferencedColumnName
FROM 
    sys.foreign_keys AS f
JOIN 
    sys.foreign_key_columns AS fc ON f.object_id = fc.constraint_object_id
JOIN 
    sys.tables AS t ON fc.parent_object_id = t.object_id
JOIN 
    sys.columns AS c ON fc.parent_object_id = c.object_id AND fc.parent_column_id = c.column_id
JOIN 
    sys.tables AS rt ON fc.referenced_object_id = rt.object_id
JOIN 
    sys.columns AS rc ON fc.referenced_object_id = rc.object_id AND fc.referenced_column_id = rc.column_id
WHERE 
    t.name = 'FactSales';

/*FK__FactSales__DateK__3F466844
FK__FactSales__ShipT__403A8C7D
FK__FactSales__BillT__412EB0B6
FK__FactSales__Custo__4222D4EF
FK__FactSales__Produ__4316F928*/

