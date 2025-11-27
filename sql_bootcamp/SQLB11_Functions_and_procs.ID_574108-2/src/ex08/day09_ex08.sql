DROP FUNCTION IF EXISTS fnc_fibonacci(integer);
CREATE OR REPLACE FUNCTION fnc_fibonacci(pstop integer DEFAULT 10)
RETURNS TABLE (fibonacci_number integer) AS  
$$
	WITH RECURSIVE fibonacci AS(
	SELECT 1 AS prev, 0 as curr
	union all 
	select curr, prev + curr
	from fibonacci
	WHERE prev + curr  < pstop
	)
    SELECT curr FROM fibonacci
$$ LANGUAGE SQL;

SELECT * FROM fnc_fibonacci(20);
SELECT * FROM fnc_fibonacci();
