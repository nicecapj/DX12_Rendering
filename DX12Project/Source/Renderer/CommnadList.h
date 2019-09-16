#pragma once

class CommandListBase
{
public:
	CommandListBase()
	{

	}
};

class CommandListExecutor
{
public:
	virtual void Execute(CommandListBase& InCommandList) = 0;
	virtual void FlushCommands() = 0;
};

template<class TCommand>
struct CommandBase
{
	void ExecuteAndDestruct(CommandListBase& InCmdList)
	{
		TCommand* pCmd = static_cast<TCommand>(this);
		if (pCmd)
		{
			pCmd->Execute(InCmdList);
			pCmd->~TCommand();
		}
	}
};

static CommandListExecutor* GCommandListExecutor;