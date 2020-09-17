/*
*** 회사 안에 여러개의 프로젝트 중에서 몇몇 프로젝트들은 특정 프로젝트가 완료 되어야만
*** 진행 할 수 있는 프로젝트가 있다. 프로젝트의 목록과 각 프로젝트간 의존 여부를 input
*** 으로 받고 의존도에 입각한 프로젝트의 진행 순서를 출력하라.
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
    Project();
    Project(string name) : mName(name), mMarked(false)
    {
        this->mDependencies = new vector<Project>();
    }
    string GetName() const;
    void SetName(string const name);
    vector<Project>* GetDependencies() const;
    bool GetMarked() const;
    constexpr void SetMarked(bool const mark);
    void AddProjectDependency(const Project* project) const;
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
void Project::AddProjectDependency(const Project* project) const
{
    vector<Project>::iterator iter = std::find(mDependencies->begin(), mDependencies->end(), project);
    
    if (iter == mDependencies->end())
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
        projects->insert(std::pair<string, Project>(names[0][index], Project(names[0][index])));
    }
}

void ProjectManager::addDependencies(const vector<vector<string>>& dependencies)
{
    for (vector<vector<string>>::iterator::value_type dependency : dependencies)
    {
        const Project before = findProject(dependency[0]);
        const Project after = findProject(dependency[1]);
        after.AddProjectDependency(&before);
    }
}

void ProjectManager::buildOrderRecursive(Project& project, vector<Project>* ordered)
{
    if (!project.GetDependencies()->empty())
    {
        for (Project p : *project.GetDependencies())
        {
            buildOrderRecursive(p, ordered);
        }
    }

    if (!project.GetMarked())
    {
        project.SetMarked(true);
        (*ordered)[this->index] = project;
        ++this->index;
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
    map<string, Project>::iterator iter = find(this->projects->begin(), this->projects->end(), name);
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
