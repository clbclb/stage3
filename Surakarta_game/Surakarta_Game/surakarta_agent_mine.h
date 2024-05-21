#include <memory>
#include "surakarta_agent_base.h"
#include "widget.h"
class SurakartaAgentMine : public SurakartaAgentBase {
   public:
    using SurakartaAgentBase::SurakartaAgentBase;
    SurakartaMove CalculateMove() override;
};
