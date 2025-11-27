CREATE OR REPLACE FUNCTION func_minimum(VARIADIC arr numeric[])
RETURNS NUMERIC AS 
$$ 
	SELECT min(value)
	FROM unnest(arr) AS value;
$$
LANGUAGE SQL;

SELECT func_minimum(VARIADIC arr => ARRAY[10.0, -1.0, 5.0, 4.4]);
	