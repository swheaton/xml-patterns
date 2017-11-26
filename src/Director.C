#include "Director.H"
#include "Builder.H"
#include "DirectorState.H"

Director::Director(const std::string & filename, Builder * builder)
{
	XMLTokenizer				tokenizer(filename);
	XMLTokenizer::XMLToken *		token			= 0;
	
	state = &BeforePrologState::getInstance();

	do
	{
		token		= tokenizer.getNextToken();
		state->parse(this, builder, token);

		if (token != 0)
			delete token;
	} while(token->getTokenType() != XMLTokenizer::XMLToken::NULL_TOKEN);
}