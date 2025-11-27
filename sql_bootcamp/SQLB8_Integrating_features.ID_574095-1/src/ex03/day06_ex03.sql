CREATE UNIQUE INDEX IF NOT EXISTS idx_person_discounts_unique 
ON person_discounts(person_id, pizzeria_id);

EXPLAIN ANALYZE 
SELECT *
FROM person_discounts pd 
WHERE person_id = 1 AND pd.pizzeria_id = 2;

SET enable_seqscan = OFF;

EXPLAIN ANALYZE 
SELECT *
FROM person_discounts pd 
WHERE person_id = 1 AND pd.pizzeria_id = 2;

SET enable_seqscan = ON;