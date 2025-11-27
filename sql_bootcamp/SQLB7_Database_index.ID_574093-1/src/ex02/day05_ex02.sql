CREATE INDEX IF NOT EXISTS idx_person_name 
ON person(UPPER(name));

SET enable_seqscan = OFF;

EXPLAIN ANALYZE
SELECT * FROM person 
WHERE UPPER(name) = 'ANNA';

SET enable_seqscan = On;