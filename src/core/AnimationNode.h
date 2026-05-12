#pragma once
#include "core/TransformNode.h"
#include "core/node.h"
#include "core/Value.h"

class ArmatureNode : public AbstractNode {
public:
    VISITABLE();
    Value animations;
    ArmatureNode(const ModuleInstantiation *mi, Value anims) : AbstractNode(mi), animations(std::move(anims)) {}
    std::string name() const override { return "armature"; }
};

class WeightNode : public AbstractNode {
public:
    VISITABLE();
    std::vector<std::string> bone_names;
    std::vector<float> weights;
    WeightNode(const ModuleInstantiation *mi, std::vector<std::string> b, std::vector<float> w) 
      : AbstractNode(mi), bone_names(std::move(b)), weights(std::move(w)) {}
    std::string name() const override { return "weight"; }
};

class BoneNode : public TransformNode {
public:
    VISITABLE();
    std::string bone_name;
    BoneNode(const ModuleInstantiation *mi, std::string name, const Transform3d& mat) 
      : TransformNode(mi, "bone"), bone_name(std::move(name)) {
        this->matrix = mat;
    }
    std::string name() const override { return "bone"; }

    // Override toString to explicitly bake the bone name into OpenSCAD's AST geometry cache key.
    // This prevents aggressively deduplicating identically-shaped structural bone branches.
    std::string toString() const override {
        return this->name() + "(\"" + this->bone_name + "\") " + TransformNode::toString();
    }
};

void register_builtin_animation();