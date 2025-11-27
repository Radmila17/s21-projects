CREATE OR REPLACE FUNCTION fnc_person_visits_and_eats_on_date(
	IN pperson varchar DEFAULT 'Dmitriy',
	IN pprice numeric DEFAULT 500,
	IN pdate date DEFAULT '2022-01-08'
)
RETURNS TABLE(pizzeria_name varchar)
AS 
$$
	BEGIN
		RETURN QUERY
		SELECT piz.name  -- distinct убрать 
		FROM person_visits pv
		JOIN pizzeria piz ON piz.id = pv.pizzeria_id
		JOIN menu m ON m.pizzeria_id = piz.id
		JOIN person p ON p.id = pv.person_id
		WHERE p.name = pperson AND m.price < pprice AND pv.visit_date = pdate;
	END;
$$ LANGUAGE plpgsql;
	
SELECT * FROM fnc_person_visits_and_eats_on_date(pprice := 800);
SELECT * FROM fnc_person_visits_and_eats_on_date(pperson := 'Anna', pprice := 1300, pdate := '2022-01-01');	
