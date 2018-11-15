type Tlong=record
       countElem: integer;
       Long :  array [1..100] of string;
     end;

procedure ReadTLong(f1:text; var A:Tlong; var error:boolean); //Считывать число
var
  s, s1:string;
  i, EndLine, count:integer;
  
begin
//..............................................................................Проверка на максимальное количество символов
  readln(f1, s);
  error := false;
  if length(s) > 300
  then
  begin
    writeln('Количество символов превышает максимум. (300 символов)');
    error:= true;
  end;
//..............................................................................Проверка на недопустимые символы
  for i := 1 to length(s) do
    if  not (s[i] in ['0'..'9','A','B','C','D','E','F'])
    then 
    begin
      writeln('Недопустимый символ "',s[i],'"');
      error := true;
    end;
//..............................................................................Перевод символов в числа и запись в массив
  s1 := '';
  EndLine := length(s);
  count := 0;
  if error = false
  then
  begin
    while EndLine > 0 do
    begin
      if EndLine >= 3
      then
      begin
        inc(count);
        s1 := Copy(s ,EndLine - 2, 3);
        A.Long[count] := s1;
        EndLine := EndLine - 3;
      end;
      if EndLine = 2
      then
      begin
        inc(count);
        s1 := Copy(s ,EndLine - 2, 2);
        A.Long  [count] := '0' + s1;
        EndLine := EndLine - 2;
      end;
      if EndLine = 1
      then
      begin
        inc(count);
        s1 := Copy(s ,EndLine - 1, 1);
        A.Long[count] := '00' + s1;
        EndLine := EndLine - 1;
      end;
    end;
    A.countElem := count;//Количество чисел занеcенных в массив
  end;
end;


//..............................................................................Перевод из char в integer
function CharInt(a:char):integer;
var
  x1,er:integer;
begin
  case a of
    'A': x1 := 10;
    'B': x1 := 11;
    'C': x1 := 12;
    'D': x1 := 13;
    'E': x1 := 14;
    'F': x1 := 15;
    '0'..'9': val(a,x1,er);
  end;
CharInt := x1;
end;
//..............................................................................Перевод из integer в char
function IntChar(a:integer):char;
var
  s:string;
begin
  s := '0123456789ABCDEF';
  IntChar := s[a+1];
end;
//..............................................................................Сложение первого числа элемента массива со вторым числом элемента массива
procedure add3TLong(first:string; second:string; var add:string; var ostatok:integer);
type ElementAdd=record
       ostatok: integer;
       sumChisel: integer;
     end;
var 
  matrica : array [0..15,0..15] of ElementAdd;
  i, j, sum, ostatokSUM:integer;
begin
  for i := 0 to 15 do
    for j := 0 to 15 do
    begin
      matrica[i,j].ostatok := (i+j) div 16;
      matrica[i,j].sumChisel := (i+j) mod 16;
    end;
    add := '';
      for i := 3 downto 1 do 
      begin
        ostatokSUM := 0;
        sum := matrica[CharInt(first[i]),CharInt(second[i])].sumChisel + ostatok;
        if sum = 16
        then
          ostatokSUM := 1;
        add :=  IntChar(sum mod 16) + add;
        ostatok := matrica[CharInt(first[i]),CharInt(second[i])].ostatok + ostatokSUM;
      end;
end;


{||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||}
procedure addTLong(firstMass:Tlong; secondMass:Tlong; var addMass:Tlong);
var
  ostatokElem, countAdd , elementFirstMass, elementSecondMass, i, countWhile: integer;
  secondMassMore : boolean;
  sumElem : string;
begin
  if firstMass.countElem < secondMass.countElem
  then
  begin
    addMass.countElem := firstMass.countElem;
    secondMassMore := true;
  end
  else
  begin
    addMass.countElem := secondMass.countElem;
    secondMassMore := false;
  end;
  for i := 1 to addMass.countElem do
  begin
    add3TLong(firstMass.Long[i], secondMass.Long[i], sumElem, ostatokElem);
    addMass.Long[i] := sumElem;
  end;
  if ostatokElem = 1
  then
  begin
    if secondMassMore = true 
    then
    begin
      for i := addMass.countElem to secondMass.countElem do
      begin
        add3Tlong(secondMass.Long[i], '000', sumElem, ostatokElem);
        addMass.Long[i] := sumElem;
        inc(addMass.countElem);
        if i = addMass.countElem
        then
        addMass.Long[addMass.countElem] := IntChar(ostatokElem);
      end;
    end
    else
    begin
      for i := addMass.countElem to firstMass.countElem do
      begin
        add3Tlong(firstMass.Long[i], '000', sumElem, ostatokElem);
        addMass.Long[i] := sumElem;
        inc(addMass.countElem);
        if i = addMass.countElem
        then
        addMass.Long[addMass.countElem] := IntChar(ostatokElem);
      end;
    end;
  end;  
end;



var
  f1:text;
  i, numbChisla:integer;
  firstMass, secondMass, addMass :Tlong;
  error:boolean;
begin
  assign(f1, 'chisla.txt');
  reset(f1);
  numbChisla := 0;
  while not eof(f1) do 
  begin
    inc(numbChisla);
    if numbChisla = 1
    then
      ReadTLong(f1, firstMass, error);
    if numbChisla = 2
    then
      ReadTLong(f1, secondMass, error);
  end;
  addTLong (firstMass, secondMass, addMass);
  
        write(firstMass.countElem, ' ');
        for i := 1 to firstMass.countElem do
        begin
          write(firstMass.Long[i]);
          write(' ');
        end;
        writeln;
        write(secondMass.countElem, ' ');
        for i := 1 to secondMass.countElem do
        begin
          write(secondMass.Long[i]);
          write(' ');
        end;
        writeln;
        write(addMass.countElem, ' ');
        for i := 1 to addMass.countElem do
        begin
          write(addMass.Long[i]);
          write(' ');
        end;
end.