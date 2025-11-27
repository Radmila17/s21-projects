CREATE SEQUENCE IF NOT EXISTS seq_person_discounts
START 1;

SELECT setval('seq_person_discounts', (SELECT COALESCE(MAX(id), 0) FROM person_discounts) + 1, false);


ALTER TABLE person_discounts 
ALTER COLUMN id SET DEFAULT nextval('seq_person_discounts');

DROP SEQUENCE seq_person_discounts CASCADE;

SELECT * FROM person_discounts ;
SELECT * FROM seq_person_discounts;

SELECT count(*)=1 AS check1,
      max("start_value") = 1 AS check2,
      max("last_value") > 5 AS check3
FROM pg_sequences
WHERE sequencename = 'seq_person_discounts'