#include "node.h"


bool EmptyNode::Evaluate(const Date& date, const string& event) const {
    return true;
}


DateComparisonNode::DateComparisonNode(const Comparison& cmp, const Date& date)
    : _cmp(cmp), _date(date) {};

bool DateComparisonNode::Evaluate(const Date& date, const string& event) const {
    switch(_cmp) {
    case Comparison::Less:
        return date < _date;
    case Comparison::LessOrEqual:
        return date <= _date;
    case Comparison::Greater:
        return date > _date;
    case Comparison::GreaterOrEqual:
        return date >= _date;
    case Comparison::Equal:
        return date == _date;
    case Comparison::NotEqual:
        return !(date == _date);
    }
}


EventComparisonNode::EventComparisonNode(const Comparison& cmp, const string& event)
    : _cmp(cmp), _event(event) {};

bool EventComparisonNode::Evaluate(const Date& date, const string& event) const {
    switch(_cmp) {
    case Comparison::Less:
        return event < _event;
    case Comparison::LessOrEqual:
        return event <= _event;
    case Comparison::Greater:
        return event > _event;
    case Comparison::GreaterOrEqual:
        return event >= _event;
    case Comparison::Equal:
        return event == _event;
    case Comparison::NotEqual:
        return !(event == _event);
    }
}


LogicalOperationNode::LogicalOperationNode(
    const LogicalOperation& lop,
    const shared_ptr<Node>& left,
    const shared_ptr<Node>& parsed
) : op_(lop), left_(left), parsed_(parsed) {}

bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const {
    if (op_ == LogicalOperation::And) {
        bool ret = (left_->Evaluate(date, event) && parsed_->Evaluate(date,event));
        return ret;
    }
    else return (left_->Evaluate(date, event) || parsed_->Evaluate(date,event));
}
