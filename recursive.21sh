recursive := {
	i1 := $1;
	i2 := $2;
	if $[i1 < i2] then {
		echo $1;
		recursive $[i1 + 1] $2;
	};
};
recursive $1 $2;
