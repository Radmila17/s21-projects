SELECT generated_date AS missing_date
FROM v_generated_dates
EXCEPT
SELECT visit_date
FROM person_visits pv 
ORDER BY missing_date;

SELECT generated_date AS missing_date
FROM v_generated_dates
WHERE NOT EXISTS
(SELECT visit_date
FROM person_visits pv
WHERE pv.visit_date = v_generated_dates.generated_date)
ORDER BY missing_date;

