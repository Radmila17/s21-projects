CREATE OR REPLACE VIEW v_persons_female  AS 
SELECT *
FROM person p 
WHERE gender = 'female';

CREATE OR REPLACE VIEW v_persons_male AS 
SELECT *
FROM person p 
WHERE gender = 'male';

SELECT * FROM v_persons_female;
SELECT * FROM v_persons_male;