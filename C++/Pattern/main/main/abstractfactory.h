class Scanner
{
public:
	virtual ~Scanner() = 0;
};

class Parser
{
public:
	virtual ~Parser() = 0;
};

class CodeGenerator
{
public:
	virtual ~CodeGenerator() = 0;
};

class Optimizer{
public:
	virtual ~Optimizer() = 0;
};
/*
Scanner::~Scanner(){}
Parser::~Parser(){}
CodeGenerator::~CodeGenerator(){}
Optimizer::~Optimizer(){}
*/
class HPScanner : public Scanner{};
class HPParser : public Parser{};
class HPCodeGenerator : public CodeGenerator{};
class HPOptimizer : public Optimizer{};

class SunScanner : public Scanner{};
class SunParser : public Parser{};
class SunCodeGenerator : public CodeGenerator{};
class SunOptimizer : public Optimizer{};

class CompilerFactory{
public:
	virtual Scanner* CreateScanner() = 0;
	virtual Parser* CreateParser() = 0;
	virtual CodeGenerator * CreateCodeGenerator() = 0;
	virtual Optimizer* CreateOptimizer() = 0;
};


class HPCompilerFactory : public CompilerFactory{
public:
	Scanner* CreateScanner() { return new HPScanner; }
	Parser* CreateParser() { return new HPParser; }
	CodeGenerator * CreateCodeGenerator()  { return new HPCodeGenerator; }
	Optimizer* CreateOptimizer()  { return new HPOptimizer; }
};

class SunCompilerFactory : public CompilerFactory{
public:
	Scanner* CreateScanner() { return new SunScanner; }
	Parser* CreateParser() { return new SunParser; }
	CodeGenerator * CreateCodeGenerator() { return new SunCodeGenerator; }
	Optimizer* CreateOptimizer() { return new SunOptimizer; }
};




