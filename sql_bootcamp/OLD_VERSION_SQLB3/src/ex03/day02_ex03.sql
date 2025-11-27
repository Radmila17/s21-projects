WITH ten_dates AS 
	(SELECT generate_series('2022-01-01', '2022-01-10', INTERVAL '1 day')::date AS ten_dates)
select ten_dates  AS missing_date
FROM (SELECT visit_date FROM person_visits pv WHERE pv.person_id = 1 OR pv.person_id = 2) pv
RIGHT JOIN ten_dates ON  pv.visit_date = ten_dates.ten_dates 
WHERE pv.visit_date IS NULL;


/*Just for me with CTE*/
WITH person_visits_date AS 
	(SELECT visit_date FROM person_visits pv  WHERE pv.person_id = 1 OR pv.person_id = 2),
	ten_dates AS 
	(SELECT generate_series('2022-01-01', '2022-01-10', INTERVAL '1 day')::date AS ten_dates)
SELECT ten_dates
FROM ten_dates 
LEFT JOIN person_visits_date pvd ON ten_dates = pvd.visit_date
WHERE pvd.visit_date IS NULL;
