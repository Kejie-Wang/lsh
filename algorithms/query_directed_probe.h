#ifndef _LSH_QUERY_DIRECTED_PROBE_
#define _LSH_QUERY_DIRECTED_PROBE_

#include <vector>
#include <algorithms>
#include <queue>
#include <bitset>
#include "../util/lsh_table.h"

namespace lsh
{

typedef struct _PerturbationItem
{
	unsigned int hash_function_index;
	int perturbation;	//-1 or +1
	double value;
} PerturbationItem;

typedef std::pair<double, std::set<unsigned int> > ScoreSetPair;	//score and a set of item index
typedef std::vector<pair<int, int> > PerturbationVector;

bool pertubation_item_cmp(const PerturbationItem& item1, const PerturbationItem& item2)
{
	return item1.value < item2.value;
}

template<typename T>
class QueryDirectedProbe
{

	typedef T ElementType;

public:

	QueryDirectedProbe()
	{
	}

	/**Constructor using a query vector
	 */
	QueryDirectedProbe(lsh::LshTable<ElementType>* table, ElementType* query, unsigned int key_size)
	{
		table_ = table;
		query_ = query;
		key_size_ = key_size;

		perturbation_items_.resize(2 * key_size_);
		for(int i=0;i<key_size_;++i)
		{
			PerturbationItem& item_minus_one = perturbation_items_[2*i];
			item_minus_one.hash_function_index = i;
			item_minus_one.perturbation = -1;
			item_minus_one.value = table_.query_dist(i, query_);

			PerturbationItem& item_plus_one = perturbation_items_[2*i+1];
			item_plus_one.hash_function_index = i;
			item_plus_one.perturbation = +1;
			item_plus_one.value = w - item_minus_one.value;
		}
		sort(perturbation_items_.begin(), perturbation_items_.end(), pertubation_item_cmp);

		//initialize the heap with the set {0}, the set with lowest score
		std::set<unsigned int> s;
		s.insert(0);
		min_heap_.insert(ScoreSetPair(score(s), s));

	}

	std::vector<PerturbationVector> genNextPerturbationSet()
	{
		PerturbationVector perturbation_vec = getPerturbationVec(min_heap_.top());

		ScoreSetPair min = min_heap_.top();
		min_heap_.pop();
		std::set<unsigned int> shift_set = shift(min);
		std::set<unsigned int> expand_set = expand(min);
		min_heap_.insert(ScoreSetPair<score(shift_set), shift_set>);
		min_heap_.insert(ScoreSetPair<score(expand_set), expand_set>);

		return perturbation_vec;
	}


private:
	double score(const ScoreSetPair& index)
	{
		double s = 0;
		ScoreSetPair::iterator it = index.begin();
		for(;it!=index.end();++it)
			s += perturbation_items_[*it].value;
		return s;
	}

	inline std::set<unsigned int> shift(const std::set<unsigned int>& perturbation_set)
	{
		unsigned int& max = *perturbation_set.rbegin();
		max += 1;
	}

	inline std::set<unsigned int> expand(const std::set<unsigned int>& perturbation_set)
	{
		unsigned int max = *perturbation_set.rbegin();
		perturbation_set.insert(max+1);
	}

	inline PerturbationVector getPerturbationVec(const std::set<unsigned int>& perturbation_set)
	{
		PerturbationVector perturbation_vec;

		std::set<unsigned int>::iterator it = perturbation.begin();
		for(;it!=perturbation_set.end();++it)
		{
			int hash_function_index = perturbation_items_[*it].hash_function_index;
			int perturbation = perturbation_items_[*it].perturbation;
			perturbation_vec.push_back(std::pair<int, int>(hash_function_index, perturbation));
		}

		return perturbation_vec;
	}

private:

	lsh::LshTable<ElementType>* table_;

	ElementType* query_;

	unsigned int key_size_;

	std::vector<PerturbationItem> perturbation_items_;

	std::priority_queue<ScoreSetPair> min_heap_;
};

}

#endif //_LSH_QUERY_DIRECTED_PROBE_