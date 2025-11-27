DROP FUNCTION IF EXISTS fnc_persons_female;
DROP FUNCTION IF EXISTS fnc_persons_male;

CREATE OR REPLACE FUNCTION fnc_persons(IN pgender varchar DEFAULT 'female')
RETURNS table(
	id bigint,
    name varchar,
    age integer,
    gender varchar,
    address varchar)
 AS 
 $$
 	SELECT * FROM person
 	WHERE gender = pgender
 $$
 LANGUAGE SQL;


select *
from fnc_persons(pgender := 'male');

select *
from fnc_persons();
