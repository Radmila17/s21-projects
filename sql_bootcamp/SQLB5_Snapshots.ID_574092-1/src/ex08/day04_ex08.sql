DROP MATERIALIZED VIEW mv_dmitriy_visits_and_eats;
DROP VIEW v_generated_dates, v_persons_female, v_persons_male;


SELECT DISTINCT matviewname, viewname 
FROM  pg_matviews, pg_views
WHERE viewname  LIKE 'v_%';
