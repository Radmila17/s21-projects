COMMENT ON TABLE person_discounts IS 'This is a table with discount calculations for each person in specific pizzerias.';
COMMENT ON COLUMN person_discounts.id IS 'Primary key identifier for discount record';
COMMENT ON COLUMN person_discounts.person_id IS 'Foreign key referencing the person who receives the discount';
COMMENT ON COLUMN person_discounts.pizzeria_id IS 'Foreign key referencing the pizzeria where discount is valid';
COMMENT ON COLUMN person_discounts.discount IS 'Discount percentage value (0-100%) for this person in this pizzeria';

SELECT obj_description('person_discounts'::regclass);

SELECT 
    column_name,
    col_description((table_schema || '.' || table_name)::regclass::oid, ordinal_position) as column_comment
FROM information_schema.columns 
WHERE table_name = 'person_discounts';

SELECT count(*) = 5 AS check
FROM pg_description
WHERE objoid = 'person_discounts'::regclass

SELECT column_default::integer = 0 AS check
FROM information_schema.columns
WHERE COLUMN_NAME = 'discount'
  AND TABLE_NAME = 'person_discounts'
  
  SELECT count(*) = 5 AS check
FROM pg_description
WHERE objoid = 'person_discounts'::regclass