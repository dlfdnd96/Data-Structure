/*
*** ȸ�� �ȿ� �������� ������Ʈ �߿��� ��� ������Ʈ���� Ư�� ������Ʈ�� �Ϸ� �Ǿ�߸�
*** ���� �� �� �ִ� ������Ʈ�� �ִ�. ������Ʈ�� ��ϰ� �� ������Ʈ�� ���� ���θ� input
*** ���� �ް� �������� �԰��� ������Ʈ�� ���� ������ ����϶�.
*** projects: a, b, c, d, e, f, g
*** dependencies: (f,a), (f,b), (f,c), (b,a), (c,a), (a,e), (b,e), (d,g)
*/
#include <iostream>
#include <vector>
#include <map>
#include <string>

using std::cout;
using std::endl;
using std::vector;
using std::map;
using std::string;

class Project
{
public:
    Project(string name) : mName(name), mMarked(false)
    {
        this->mDependencies = new vector<Project>();
    }
    string GetName() const;
    void SetName(string const name);
    vector<Project>* GetDependencies() const;
    bool GetMarked() const;
    constexpr void SetMarked(bool const mark);
    void AddProjectDependency(Project* project) const;
    vector<Project>* GetProjectDependencies() const;

private:
    string mName;
    vector<Project>* mDependencies;
    bool mMarked;
}; // end Project class

/* Getter, Setter */
string Project::GetName() const
{
    return mName;
}
void Project::SetName(string const name)
{
    this->mName = name;
}
vector<Project>* Project::GetDependencies() const
{
    return this->mDependencies;
}
bool Project::GetMarked() const
{
    return this->mMarked;
}
constexpr void Project::SetMarked(bool const mark)
{
    this->mMarked = mark;
}

/* function */
void Project::AddProjectDependency(Project* project) const
{
    bool isNewProject = true;
    for (vector<Project>::iterator iter = this->mDependencies->begin(); iter != this->mDependencies->end(); ++iter)
    {
        if (iter->GetName() == project->GetName())
        {
            isNewProject = false;
        }
    }
    
    if (isNewProject)
    {
        mDependencies->emplace_back(*project);
    }
}

vector<Project>* Project::GetProjectDependencies() const
{
    return this->mDependencies;
}

class ProjectManager
{
public:
    ProjectManager(const vector<string>& names, const vector<vector<string>>& dependencies)
    {
        buildProjects(&names);
        addDependencies(dependencies);
    }
    vector<Project>* BuildOrder();

private:
    void buildProjects(const vector<string>* const names);
    void addDependencies(const vector<vector<string>>& dependencies);
    Project& findProject(const string dependency) const;
    void buildOrderRecursive(Project& project, vector<Project>* ordered);
    void initMarkingFlags() const;

private:
    map<string, Project>* projects;
    int index;
}; // end ProjectManager class

/* function */
vector<Project>* ProjectManager::BuildOrder()
{
    initMarkingFlags();

    vector<Project>* ordered = new vector<Project>(this->projects->size());
    this->index = 0;
    for (map<string, Project>::iterator iter = this->projects->begin(); iter != this->projects->end(); ++iter)
    {
        buildOrderRecursive(iter->second, ordered);
    }

    return ordered;
}

void ProjectManager::buildProjects(const vector<string>* const names)
{
    this->projects = new map<string, Project>();
    for (unsigned __int32 index = 0; index < names->size(); ++index)
    {
        projects->insert(std::pair<string, Project>((*names)[index], Project((*names)[index])));
    }
}

void ProjectManager::addDependencies(const vector<vector<string>>& dependencies)
{
    for (vector<vector<string>>::iterator::value_type dependency : dependencies)
    {
        Project before = findProject(dependency[0]);
        Project after = findProject(dependency[1]);
        after.AddProjectDependency(&before);
    }
}

void ProjectManager::buildOrderRecursive(Project& project, vector<Project>* ordered)
{
    if (!project.GetDependencies()->empty())
    {
        for (Project p : *(project.GetDependencies()))
        {
            buildOrderRecursive(p, ordered);
        }
    }

    if (!project.GetMarked())
    {
        project.SetMarked(true);
        (*ordered)[this->index] = project;
        ++(this->index);
    }
}

void ProjectManager::initMarkingFlags() const
{
    for (map<string, Project>::iterator iter = this->projects->begin(); iter != this->projects->end(); ++iter)
    {
        iter->second.SetMarked(false);
    }
}

Project& ProjectManager::findProject(const string name) const
{
    map<string, Project>::iterator iter = this->projects->find(name);

    return iter->second;
}

int main()
{
    vector<string> projects = { "a", "b", "c", "d", "e", "f", "g" };
    vector<vector<string>> dependencies = { {"f", "a"}, {"f", "b"}, {"f", "c"}, {"b", "a"}, {"c", "a"}, {"a", "e"}, {"b", "e"}, {"d", "g"} };
    ProjectManager* pm = new ProjectManager(projects, dependencies);
    vector<Project>* ps = pm->BuildOrder();
    for (int index = 0; index < ps->size(); ++index)
    {
        if (!ps[index].empty())
        {
            cout << (*ps)[index].GetName() + " ";
        }
    }
    
    return 0;
}
